#ifndef ROOMGROUP_HPP
#define ROOMGROUP_HPP

#include <memory>
#include <list>
#include <time.h>
#include <vector>
#include "game/rooms/Room.hpp"
#include "components/Hitbox.hpp"

class RoomGroup: public GameObject
{
public:
   void generateRoomGrid(int roomCount);
   bool isInsideRoom(sf::FloatRect hbox);
   sf::FloatRect getRoom(sf::FloatRect hbox);
   Room* getRoom(int room_num);
   Room* getRoomInside(sf::FloatRect hbox);
   std::vector<std::shared_ptr<Room>> rooms;
protected:
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
