#include "game/rooms/RoomGroup.hpp"
#include <iostream>
void RoomGroup::generateRoomGrid(int roomCount)
{
    srand (time(NULL));
    roomCount = 200;
    // TODO:  Figure out total grid size based on difficulty: for now demo is size 3
    std::unique_ptr<Room> currRoom;
    std::unique_ptr<Room> rightDoor;
    std::unique_ptr<Room> bottomDoor;
    int houseHeight = 10;
    int houseWidth = 10;
    int roomGrid [houseWidth][houseHeight];
    for(int i = 0; i < houseWidth; i++){
        for(int j = 0; j < houseHeight; j++){
            roomGrid[i][j] = -1;
        }
    }
    // set values around center to 0
    roomGrid[4][4] = 1;
    roomGrid[3][4] = 0;
    roomGrid[5][4] = 0;
    roomGrid[4][3] = 0;
    roomGrid[4][5] = 0;
    int roomsGenerated = 1;
    while(roomsGenerated != roomCount)
    {
        // select random room with 0
        int x = rand() % houseHeight;
        int y = rand() % houseWidth;
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
                currRoom->rect.setSize(sf::Vector2f(512, 320));
                currRoom->rect.setPosition((512+10) * i, (320+10) * j);
                currRoom->setPosition(currRoom->rect.getPosition());
                currRoom->init();
                // When adding doors we have to make sure they extend into each room
                // approximately the size of our character hitboxes
                // Add right facing-door
                if(i+1 < houseWidth && roomGrid[i+1][j] == 1){
                  rightDoor = std::unique_ptr<Room>(new Room());
                  rightDoor->rect.setSize(sf::Vector2f(32, 64));
                  rightDoor->rect.setPosition(currRoom->getPosition().x + 512 - 16, currRoom->getPosition().y + 160 - 32);
                  rightDoor->setPosition(rightDoor->rect.getPosition());
                }
                // Add bottom facing door
                if(j+1 < houseHeight && roomGrid[i][j+1] == 1){
                  bottomDoor = std::unique_ptr<Room>(new Room());
                  bottomDoor->rect.setSize(sf::Vector2f(64, 32));
                  bottomDoor->rect.setPosition(currRoom->getPosition().x + 256 - 32, currRoom->getPosition().y + 320 - 16);
                  bottomDoor->setPosition(bottomDoor->rect.getPosition());
                }

                this->rooms.push_back(std::move(currRoom));
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
    return false;
}

void RoomGroup::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto a = rooms.begin(); a != rooms.end(); a++){
        target.draw(**a);
    }
}
