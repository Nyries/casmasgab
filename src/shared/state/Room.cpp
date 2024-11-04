//
// Created by louismmassin on 11/4/24.
//

#include "Room.h"

namespace state {
    Room::Room(RoomName name): Location(ROOM), name(name) {
    }

    RoomName Room::getName() {
        return name;
    }

    std::vector<std::shared_ptr<Door> >& Room::getDoorList() {
        return doorList;
    }

}