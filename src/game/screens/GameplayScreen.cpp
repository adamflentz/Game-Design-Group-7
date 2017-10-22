#include "game/screens/GameplayScreen.hpp"
#include "engine/Random.hpp"
#include <iostream>
#include <time.h>

void GameplayScreen::init()
{
    rando = std::unique_ptr<Rando>(new Rando());
    rando->setGroup(&group);
    this->addChild(std::move(rando));
    this->GenerateRoomGrid(3);
}

void GameplayScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
}


void GameplayScreen::GenerateRoomGrid(int RoomCount)
{
    srand (time(NULL));
    // TODO:  Figure out total grid size based on difficulty: for now demo is size 3
    int houseHeight = 3;
    int houseWidth = 3;
    int roomGrid [houseWidth][houseHeight];
    roomGrid[1][1] = 1;
    roomGrid[0][1] = 0;
    roomGrid[2][1] = 0;
    roomGrid[1][0] = 0;
    roomGrid[1][2] = 0;
    int roomsGenerated = 1;
    while(roomsGenerated != RoomCount)
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
                currRoom->setRoomPosition((32 * i + 1), (32 * j + 1));
                group.addChild(std::move(currRoom));
            }
        }
    }
        // TODO: Add specific roomcount option
       
}