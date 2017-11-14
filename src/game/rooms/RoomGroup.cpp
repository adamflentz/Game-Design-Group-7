#include "game/rooms/RoomGroup.hpp"
#include <iostream>
void RoomGroup::generateRoomGrid(int roomCount)
{
    srand (time(NULL));
    roomCount = 200;
    // TODO:  Figure out total grid size based on difficulty: for now demo is size 3
    std::unique_ptr<Room> currRoom;
    std::unique_ptr<Room> currDoor;

    int houseHeight = 20,
        houseWidth  = 20;

    int roomGrid[houseWidth][houseHeight];
    
    // initialize all values in grid to -1 to remove junk data
    for(int i = 0; i < houseWidth * houseHeight; i++) 
        roomGrid[i % houseWidth][i / houseHeight] = -1;
    int cx = (houseWidth-1) / 2,
        cy = (houseHeight-1) / 2;
    // since we're building from the center we set values around center to 0
    roomGrid[cx][cy]   = 1;
    roomGrid[cx-1][cy] = 0;
    roomGrid[cx+1][cy] = 0;
    roomGrid[cx][cy-1] = 0;
    roomGrid[cx][cy+1] = 0;

    int roomsGenerated = 1;
    while(roomsGenerated != roomCount)
    {
        // select random room with 0
        int x = rand() % houseWidth;
        int y = rand() % houseHeight;
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
                // When adding doors we have to make sure they extend into each room
                // approximately the size of our character hitboxes
                // Add right facing-door
                if(i+1 < houseWidth && roomGrid[i+1][j] == 1){
                    currDoor = std::unique_ptr<Room>(new Room());
                    currDoor->rect.setSize(sf::Vector2f(32 * 3, 64));
                    currDoor->rect.setPosition(currRoom->getPosition().x + 256 - 32, currRoom->getPosition().y + 80 - 32);
                    currDoor->setPosition(currRoom->rect.getPosition());
                    currDoor->init();
                    this->rooms.push_back(std::move(currDoor));
                }
                // Add bottom facing door
                if(j+1 < houseHeight && roomGrid[i][j+1] == 1){
                    currDoor = std::unique_ptr<Room>(new Room());
                    currDoor->rect.setSize(sf::Vector2f(64, 32 * 3));
                    currDoor->rect.setPosition(currRoom->getPosition().x + 128 - 32, currRoom->getPosition().y + 160 - 16);
                    currDoor->setPosition(currRoom->rect.getPosition());
                    currDoor->init();
                    this->rooms.push_back(std::move(currDoor));
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
