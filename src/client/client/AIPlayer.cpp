//
// Created by louismmassin on 12/18/24.
//
#include "AIPlayer.h"

#include <utility>
#include <ai/RandomAI.h>

namespace client {
    AIPlayer::AIPlayer(engine::Engine &engine, state::PlayerState &playerState, std::string name, std::unique_ptr<ai::AI> ai): Player(engine, playerState, false, name) , ai(move(ai)){
    }

    engine::CommandId AIPlayer::chooseAction() {
        return ai->chooseAction();
    }

    engine::Move AIPlayer::chooseMoveDirection() {
        return ai->chooseMoveDirection();
    }

    state::Door& AIPlayer::chooseDoor(const std::vector<state::Door *> &doorList) {
        return ai->chooseDoor(doorList);
    }

    state::TripleClue AIPlayer::chooseHypothesis() {
        return ai->chooseHypothesis();
    }

    int AIPlayer::chooseACardToShowPlayer(const std::vector<const state::Card *> &cards, const Player &player) {
        return ai->chooseACardToShowClient(cards, player.getPlayerState());
    }



    state::TripleClue AIPlayer::chooseAccusation() {
        return ai->chooseAccusation();
    }

    void AIPlayer::seeACardFromPlayer(const state::Card &shownCard, const Player &cardOwner) {
        ai->seeACardFromPlayer(shownCard, cardOwner.getPlayerState());
    }

    void AIPlayer::makePlayerThrowDice() {

    }

    void AIPlayer::displayDiceResult(int result, const Player &player) {
        ai->getDiceResult(result, player.getPlayerState());
    }

    void AIPlayer::startOfTheGame() {
        ai->startOfTheGame();
    }

    void AIPlayer::seeHypothesisResponse(const state::TripleClue &hypothesis, const Player &askedPlayer, bool response) {

    }


}
