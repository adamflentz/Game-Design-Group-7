#include "game/screens/GameplayScreen.hpp"

void GameplayScreen::init()
{
    rando = std::unique_ptr<Rando>(new Rando());
    this->GenerateRoomGrid(3);
    this->addChild(std::move(roomFac[0]));
    this->addChild(std::move(rando));

}

void GameplayScreen::GenerateRoomGrid(int RoomCount)
{
    for(int i=0; i < 3; i++){
        // TODO: Add specific roomcount option
        room = std::unique_ptr<Room>(new Room());
        roomFac.push_back(std::move(room));
    }
}