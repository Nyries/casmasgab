//
// Created by louismmassin on 12/18/24.
//
#include "HumanPlayer.h"

#include <iostream>
#include <utility>
#include <engine/Engine.h>

#include "state/Weapon.h"
#include "Client.h"

namespace client {
    HumanPlayer::HumanPlayer(engine::Engine &engine, state::PlayerInfo &playerInfo, std::string& name): Player(engine, playerInfo, true, name) {

    }
}
