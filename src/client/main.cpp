#include <engine.h>
#include <state.h>
#include <client.h>
#include <render.h>
#include <ai.h>
#include <iostream>

#include <SFML/Graphics.hpp>

void test() {
    //put some code you want to run here
}

std::string gameLoop(state::State& myState, engine::Engine& myEngine, client::Client& myClient) {
    client::PlayerList& myPlayerList = myClient.getPlayerList();
    client::IO& io = myClient.getIO();
    io.startOfTheGame(myPlayerList);
    while (!myState.getAccusationSuccess()) {
        client::Player& currentPlayer = myPlayerList.getCurrent();
        state::PlayerState& currentPlayerState =  currentPlayer.getPlayerState();
        if (currentPlayerState.getCanWin()) {
            const engine::CommandId currentAction = currentPlayer.chooseAction();
            switch (currentAction) {
                case engine::HYPOTHESIS: {
                    const state::TripleClue hypothesis = currentPlayer.chooseHypothesis();
                    io.displayHypothesis(currentPlayer, hypothesis);
                    myEngine.addCommand(std::make_unique<engine::HypothesisCommand>(myEngine, currentPlayerState, hypothesis));
                    myEngine.executeCommands();
                    io.updatePlayerPositions();
                    myClient.askHypothesisToNeighbors(currentPlayer, hypothesis);
                }
                break;
                case engine::ACCUSATION: {
                    const state::TripleClue accusation = currentPlayer.chooseAccusation();
                    io.displayAccusation(currentPlayer, accusation);
                    myEngine.addCommand(std::make_unique<engine::AccusationCommand>(myEngine, currentPlayerState, accusation));
                }
                break;
                case engine::SECRET_PASSAGE: {
                    myEngine.addCommand(std::make_unique<engine::SecretPassageCommand>(myEngine, currentPlayerState));
                    myEngine.executeCommands();
                    io.updatePlayerPositions();
                    const state::TripleClue hypothesis = currentPlayer.chooseHypothesis();
                    io.displayHypothesis(currentPlayer, hypothesis);
                    myEngine.addCommand(std::make_unique<engine::HypothesisCommand>(myEngine, currentPlayerState, hypothesis));
                    myEngine.executeCommands();
                    io.updatePlayerPositions();
                    myClient.askHypothesisToNeighbors(currentPlayer, hypothesis);
                }
                break;
                case engine::MOVE_FROM_DICE: {
                    std::vector<int> diceResult = engine::Engine::dice();
                    currentPlayer.makePlayerThrowDice();
                    int remainingMoves = diceResult.at(0) + diceResult.at(1);
                    io.displayDiceResult(myPlayerList, remainingMoves, currentPlayer);
                    while (remainingMoves > 0) {
                        /*
                        if (currentPlayerState.getLocation().getType() == state::CORRIDOR or currentPlayerState.getLocation().getType() == state::DOOR) {
                            const auto& testCell = dynamic_cast<const state::Cell&>(currentPlayerState.getLocation());
                            std::cout << "coords: " << testCell.getX() << ", " << testCell.getY() << std::endl;
                        }*/
                        const auto possibleMoves = myEngine.getPossibleMoves(currentPlayerState);
                        if (possibleMoves.empty()) {
                            break;
                        }
                        const engine::Move moveDirection = currentPlayer.chooseMoveDirection();
                        if (moveDirection == engine::EXIT_ROOM) {
                            auto& currentRoom = dynamic_cast<state::Room&>(currentPlayerState.getLocation());
                            state::Door& newDoor = currentPlayer.chooseDoor(currentRoom.getDoorList());
                            myEngine.addCommand(std::make_unique<engine::MoveCommand>(myEngine, currentPlayerState, newDoor));
                        }
                        else {
                            state::Location& newLocation = myEngine.convertMoveToLocation(moveDirection);
                            myEngine.addCommand(std::make_unique<engine::MoveCommand>(myEngine, currentPlayerState, newLocation));
                        }
                        myEngine.executeCommands();
                        io.updatePlayerPositions();
                        if (currentPlayerState.getLocation().getType() == state::ROOM) {
                            const state::TripleClue hypothesis = currentPlayer.chooseHypothesis();
                            io.displayHypothesis(currentPlayer, hypothesis);
                            myEngine.addCommand(std::make_unique<engine::HypothesisCommand>(myEngine, currentPlayerState, hypothesis));
                            myEngine.executeCommands();
                            io.updatePlayerPositions();
                            myClient.askHypothesisToNeighbors(currentPlayer, hypothesis);
                            break;
                        }
                        remainingMoves--;
                    }
                    break;
                }
                default:
                    break;
            }
            myEngine.executeCommands();
            io.updatePlayerPositions();
        }
        if ( myState.getAccusationSuccess()) {
            io.displayGameEnd(currentPlayer);
            return currentPlayer.getName();
        }
        myPlayerList.next();
        myEngine.setCurrentPlayer(myPlayerList.getCurrent().getPlayerState());
    }
}

int main(int argc,char* argv[])
{

    //test();//used for testing methods

    //main
    if (argc < 3) {
        throw std::invalid_argument("program needs at least 2 parameters");
    }
    if (std::string(argv[1]) == "solovsai") {
        //Initialisation
        const std::string mapJsonPath = "../configurations/map.json";
        std::unique_ptr<client::IO> tempIO;
        if (std::string(argv[2]) == "console") {
            tempIO = std::make_unique<client::ConsoleIO>();

        } else if (std::string(argv[2]) == "render") {
            tempIO = std::make_unique<client::RenderIO>();
        }
        else {
            throw std::invalid_argument(std::string("invalid argument: ") + argv[2]);
        }
        int playerCount = tempIO->introductionToTheGame();
        state::State myState(mapJsonPath, playerCount);
        engine::Engine myEngine(myState);

        //Construction de la liste des joueurs; le joueur humain est toujours le premier de la liste
        std::vector<state::PlayerState>& playerStateVec = myState.getPlayerStateVec();
        std::vector<std::unique_ptr<client::Player>> playerVec(playerCount);
        if (std::string(argv[2]) == "console") {
            auto& consoleIO = dynamic_cast< client::ConsoleIO& >(*tempIO);
            consoleIO.setMap(myState.getMap());
            client::HumanPlayerConsole userPlayer(myEngine, playerStateVec.at(0), "User");
            playerVec.front() = std::make_unique<client::HumanPlayerConsole>(std::move(userPlayer));;
        }
        else if (std::string(argv[2]) == "render") {
            auto& renderIO = dynamic_cast< client::RenderIO& >(*tempIO);
            render::Render& myRender = renderIO.getRender();
            client::HumanPlayerRender userPlayer(myEngine, playerStateVec.at(0), "User", myRender);
            myRender.setPlayer(userPlayer);
            myRender.setMap(myState.getMap());
            myRender.setEngine(myEngine);
            myRender.setPlayerStateVec(myState.getPlayerStateVec());
            playerVec.front() = std::make_unique<client::HumanPlayerRender>(std::move(userPlayer));;
        }
        for (int i = 1; i < playerCount; i++) {
            client::AIPlayer aiPlayer(myEngine, playerStateVec.at(i), "AI " + std::to_string(i), std::make_unique<ai::EasyAI>(myEngine, playerStateVec.at(i)));
            playerVec.at(i) = std::make_unique<client::AIPlayer>(std::move(aiPlayer));
        }
        client::Client myClient(myState, myEngine, tempIO, playerVec);

        //debut de la partie
        client::PlayerList& myPlayerList = myClient.getPlayerList();
        int firstPlayerIndex = myEngine.determineFirstPlayer();
        myPlayerList.setCurrent(myPlayerList.getVector().at(firstPlayerIndex));
        myEngine.setCurrentPlayer(playerStateVec.at(firstPlayerIndex));
        myEngine.distributionCharacters();
        myEngine.dealCards();

        gameLoop(myState, myEngine, myClient);
        return 0;
    }
    if (std::string(argv[1]) == "autoplay") {

        //Initialisation
        const std::string mapJsonPath = "../configurations/map.json";
        int easyWinCount = 0;
        int mediumWinCount = 0;
        std::string winner;
        int playerCount = 4;
        for (int play = 0; play < 100; play++){
            std::unique_ptr<client::IO> tempIO;
            if (std::string(argv[2]) == "console") {
                tempIO = std::make_unique<client::ConsoleIO>();

            } else if (std::string(argv[2]) == "render") {
                tempIO = std::make_unique<client::RenderIO>();
            }
            else if (std::string(argv[2]) == "empty") {
                tempIO = std::make_unique<client::EmptyIO>();
            }
            else {
                throw std::invalid_argument(std::string("invalid argument: ") + argv[2]);
            }
            state::State myState(mapJsonPath, playerCount);
            engine::Engine myEngine(myState);

            //Construction de la liste des joueurs; le joueur humain est toujours le premier de la liste
            std::vector<state::PlayerState>& playerStateVec = myState.getPlayerStateVec();
            std::vector<std::unique_ptr<client::Player>> playerVec(playerCount);
            if (std::string(argv[2]) == "render") {
                auto& renderIO = dynamic_cast< client::RenderIO& >(*tempIO);
                render::Render& myRender = renderIO.getRender();
                myRender.setMap(myState.getMap());
                myRender.setEngine(myEngine);
                myRender.setPlayerStateVec(myState.getPlayerStateVec());
            }
            for (int i = 0; i < playerCount; i++) {
                if (i < 2) {
                    client::AIPlayer aiPlayer(myEngine, playerStateVec.at(i), "AI " + std::to_string(i + 1), std::make_unique<ai::EasyAI>(myEngine, playerStateVec.at(i)));
                    playerVec.at(i) = std::make_unique<client::AIPlayer>(std::move(aiPlayer));
                }
                else {
                    client::AIPlayer aiPlayer(myEngine, playerStateVec.at(i), "AI " + std::to_string(i + 1), std::make_unique<ai::MediumAI>(myEngine, playerStateVec.at(i)));
                    playerVec.at(i) = std::make_unique<client::AIPlayer>(std::move(aiPlayer));
                }
            }
            client::Client myClient(myState, myEngine, tempIO, playerVec);

            //debut de la partie
            client::PlayerList& myPlayerList = myClient.getPlayerList();
            int firstPlayerIndex = myEngine.determineFirstPlayer();
            myPlayerList.setCurrent(myPlayerList.getVector().at(firstPlayerIndex));
            myEngine.setCurrentPlayer(playerStateVec.at(firstPlayerIndex));
            myEngine.distributionCharacters();
            myEngine.dealCards();

            winner = gameLoop(myState, myEngine, myClient);
            //std::cout << "winner " << winner << std::endl;
            if (winner == "AI 1" or winner == "AI 2") {
                easyWinCount++;
            }else {
                mediumWinCount++;
            }
            std::cout << "Game " << play << " completed" << std::endl;
        }

        std::cout << "EasyAI wins: " << easyWinCount << ", MediumAI wins: " << mediumWinCount << std::endl;
        return 0;
    }
}