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
   sf::FloatRect getRoom(sf::FloatRect hbox);
   std::list<std::unique_ptr<Room>> rooms;
protected:
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
