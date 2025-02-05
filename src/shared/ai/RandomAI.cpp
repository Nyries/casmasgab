//
// Created by louismmassin on 1/4/25.
//
#include "RandomAI.h"

#include <engine/Engine.h>
#include <engine/UtilityFunctions.h>
#include <SFML/Graphics/RenderStates.hpp>

namespace ai {
    RandomAI::RandomAI(engine::Engine &engine, state::PlayerState &playerState):AI(engine, playerState) {
    }

    engine::CommandId RandomAI::chooseAction() {
        auto possibleActions = engine.getPossibleActions(playerState);
        const int randomIndex = engine::UtilityFunctions::randomInt(possibleActions.size());
        return possibleActions.at(randomIndex);
    }

    engine::Move RandomAI::chooseMoveDirection() {
        auto possibleMoves = engine.getPossibleMoves(playerState);
        const int randomIndex = engine::UtilityFunctions::randomInt(possibleMoves.size());
        return possibleMoves.at(randomIndex);
    }

    state::TripleClue RandomAI::chooseHypothesis() {
        state::TripleClue hypothesis{};
        int randomSuspect = engine::UtilityFunctions::randomInt(6) + 1;
        hypothesis.suspect = static_cast<state::Suspect>(randomSuspect);
        int randomWeapon = engine::UtilityFunctions::randomInt(6) + 1;
        hypothesis.weapon = static_cast<state::Weapon>(randomWeapon);
        auto locationEnum = playerState.getLocation().getType();
        if (locationEnum == state::ROOM) {
            auto& randomRoom = static_cast<state::Room&>(playerState.getLocation());
            hypothesis.room = randomRoom.getRoomName();
        } else {
            throw std::runtime_error("error");
        }
        return hypothesis;
    }


    int RandomAI::chooseACardToShowClient(const std::vector<const state::Card *> &cards, const state::PlayerState &client) {
        const int randomIndex = engine::UtilityFunctions::randomInt(cards.size());
        return randomIndex;
    }


    void RandomAI::seeACardFromPlayer(const state::Card &shownCard, const state::PlayerState &cardOwner) {
        // DO NOTHING
    }

    void RandomAI::seeHypothesisResponse(const state::TripleClue &hypothesis, const state::PlayerState &askedPlayer, bool response) {
        // DO NOTHING
    }



    state::TripleClue RandomAI::chooseAccusation() {
        state::TripleClue accusation{};
        int randomSuspect = engine::UtilityFunctions::randomInt(6) + 1;
        accusation.suspect = static_cast<state::Suspect>(randomSuspect);
        int randomWeapon = engine::UtilityFunctions::randomInt(6) + 1;
        accusation.weapon = static_cast<state::Weapon>(randomWeapon);
        int randomRoom = engine::UtilityFunctions::randomInt(9) + 1;
        accusation.room = static_cast<state::RoomName>(randomRoom);
        return accusation;
    }

    state::Door& RandomAI::chooseDoor(const std::vector<state::Door *> &doorList) {
        const int randomIndex = engine::UtilityFunctions::randomInt(doorList.size());
        return *doorList.at(randomIndex);
    }

    void RandomAI::getDiceResult(int result, const state::PlayerState &player) {
        // NOTHING
    }

    void RandomAI::startOfTheGame() {
        // NOTHING ??
    }


}
