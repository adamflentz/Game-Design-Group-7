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
   bool inSameRoom(sf::FloatRect box1, sf::FloatRect box2);
   sf::FloatRect getRoom(sf::FloatRect hbox);
   int totalRooms;
   Room* getRoom(int room_num);
   Room* getRoomInside(sf::FloatRect hbox);
   // Why have this? Just in case.
   int roomCount();
   std::vector<std::shared_ptr<Room>> rooms;
protected:
    int num_rooms = 0;
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
