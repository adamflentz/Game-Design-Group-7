#include "game/rooms/RoomGroup.hpp"
#include <iostream>
void RoomGroup::generateRoomGrid(int roomCount)
{
    srand (time(NULL));
    // TODO:  Figure out total grid size based on difficulty: for now demo is size 3
    std::unique_ptr<Room> currRoom;
    std::unique_ptr<Room> rightDoor;
    std::unique_ptr<Room> bottomDoor;
    int houseHeight = 3;
    int houseWidth = 3;
    int roomGrid [houseWidth][houseHeight];
    roomGrid[1][1] = 1;
    roomGrid[0][1] = 0;
    roomGrid[2][1] = 0;
    roomGrid[1][0] = 0;
    roomGrid[1][2] = 0;
    int roomsGenerated = 1;
    while(roomsGenerated != roomCount)
    {
        // select random room with 0
        int x = rand() % 3;
        int y = rand() % 3;
        if (roomGrid[x][y] == 0)
        {
            roomGrid[x][y] = 1;
            if(x != 0 && roomGrid[x-1][y] != 1){roomGrid[x-1][y] = 0;}
            if(x != houseWidth - 1 && roomGrid[x+1][y] != 1){roomGrid[x+1][y] = 0;}
            if(y != 0 && roomGrid[x][y - 1] != 1){roomGrid[x][y - 1] = 0;}
            if(y != houseHeight - 1 && roomGrid[x][y + 1] != 1){roomGrid[x][y + 1] = 0;}
            roomsGenerated++;
        }
    }
    for(int i = 0; i < houseWidth; i++)
    {
        for(int j = 0; j < houseHeight; j++)
        {
            if(roomGrid[i][j] == 1)
            {
                currRoom = std::unique_ptr<Room>(new Room());
                currRoom->rect.setSize(sf::Vector2f(256, 160));
                currRoom->rect.setPosition((256+10) * i, (160+10) * j);
                currRoom->setPosition(currRoom->rect.getPosition());
                currRoom->init();
                if(i+1 < houseWidth && roomGrid[i+1][j] == 1){
                  rightDoor = std::unique_ptr<Room>(new Room());
                  rightDoor->rect.setSize(sf::Vector2f(32, 64));
                  rightDoor->rect.setPosition(currRoom->getPosition().x + 256 - 16, currRoom->getPosition().y + 80 - 32);
                  rightDoor->setPosition(rightDoor->rect.getPosition());
                }

                if(j+1 < houseHeight && roomGrid[i][j+1] == 1){
                  bottomDoor = std::unique_ptr<Room>(new Room());
                  bottomDoor->rect.setSize(sf::Vector2f(64, 32));
                  bottomDoor->rect.setPosition(currRoom->getPosition().x + 128 - 32, currRoom->getPosition().y + 160 - 16);
                  bottomDoor->setPosition(bottomDoor->rect.getPosition());
                }

                this->rooms.push_back(std::move(currRoom));
                if(rightDoor)
                {
                  rightDoor->init();
                  this->doors.push_back(std::move(rightDoor));
                }
                if(bottomDoor)
                {
                  bottomDoor->init();
                  this->doors.push_back(std::move(bottomDoor));
                }
            }
        }
    }
        // TODO: Add specific roomcount option
}
// checks if a hitbox is inside a room
bool RoomGroup::isInsideRoom(sf::FloatRect hbox)
{
    for(auto r = rooms.begin(); r != rooms.end(); r++){
        sf::FloatRect hbox2 = (*r)->hbox;
        // check if hbox is inside room hitbox
        if(
            (hbox.top >= hbox2.top && hbox.top + hbox.height <= hbox2.top + hbox2.height) &&
            (hbox.left >= hbox2.left && hbox.left + hbox.width <= hbox2.left + hbox2.width)
        )
        {
            return true;
        }
    }
    for(auto r = doors.begin(); r != doors.end(); r++){
        sf::FloatRect hbox2 = (*r)->hbox;
        // check if hbox is inside room hitbox
        if(
            hbox2.intersects(hbox)
        )
        {
            return true;
        }
    }
    return false;
}

void RoomGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto a = rooms.begin(); a != rooms.end(); a++){
        target.draw(**a);
    }

    for(auto a = doors.begin(); a != doors.end(); a++){
        target.draw(**a);
    }

}
