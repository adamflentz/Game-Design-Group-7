#ifndef ROOMGROUP_HPP
#define ROOMGROUP_HPP

#include <memory>
#include <list>
#include <time.h>
#include "game/rooms/Room.hpp"
#include "components/Hitbox.hpp"

class RoomGroup: public GameObject
{
public:
   void generateRoomGrid(int roomCount);
   bool isInsideRoom(sf::FloatRect hbox);
   std::list<std::unique_ptr<Room>> rooms;
   std::list<std::unique_ptr<Room>> doors;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
