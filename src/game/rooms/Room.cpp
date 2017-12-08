#include <vector>
#include <iostream>
#include "game/rooms/Room.hpp"

void Room::init()
{
    if(!isDoor)
      hbox = Hitbox(
        rect.getPosition().x + 32,
        rect.getPosition().y + 64 ,
        rect.getSize().x - 64,
        rect.getSize().y - 96);
    else{
      hbox = Hitbox(
        rect.getPosition().x,
        rect.getPosition().y,
        rect.getSize().x,
        rect.getSize().y);

      if(isBottom){
        rect.setSize(sf::Vector2f(rect.getSize().x,
          rect.getSize().y / 2 ));
        rect.move(0, 16);
      }else{
        rect.setSize(sf::Vector2f(rect.getSize().x / 2,
          rect.getSize().y ));
        rect.move(16, 0);
      }
      rect.setFillColor(sf::Color::Black);
    }
    hbox.init();
    //rect.setOutlineColor(sf::Color::White);
    //rect.setOutlineThickness(3);
}

void Room::setRoomType(int type)
{
    std::cout << "Room type " << type << std::endl;
    switch(type){
      case 1:
        room_setup = "armory";
        //spears
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //hay?
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(8);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //chest
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //table
        clueCoordinates.push_back(6);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //bookshelf
        clueCoordinates.push_back(11);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //chest
        clueCoordinates.push_back(11);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //chest
        clueCoordinates.push_back(14);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);  
      break;
      case 2:
        room_setup = "throne";
        //queen
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        //pedestal
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        //column
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //column
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(8);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(3);
        //column
        clueCoordinates.push_back(13);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //column
        clueCoordinates.push_back(13);
        clueCoordinates.push_back(8);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(3);
      break;
      case 3:
        room_setup = "grave";
        //stump
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        //columnleafy
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(3);
        //column
        clueCoordinates.push_back(11);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(3);
        //grave
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //rock
        clueCoordinates.push_back(12);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
      break;
      case 4:
        room_setup = "parlor";
        //chest
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //dresser
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1 );
        //table
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(3);
        //plant1
        clueCoordinates.push_back(6);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //plant2
        clueCoordinates.push_back(9);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //plant3
        clueCoordinates.push_back(6);
        clueCoordinates.push_back(9);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //plant4
        clueCoordinates.push_back(9);
        clueCoordinates.push_back(9);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //couch
        clueCoordinates.push_back(11);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        //piano
        clueCoordinates.push_back(11);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(3);
      break;
      case 5:
        room_setup = "lounge";
        //candle
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //fireplace
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        //couch
        clueCoordinates.push_back(8);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        //table
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(2);
        //china
        clueCoordinates.push_back(11);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
      break;
      case 6:
        room_setup = "kitchen";
        //furniture
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(1);
        //tablechairs
        clueCoordinates.push_back(6);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(2);
        //kitchenstoveshit
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(11);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(1); 
      break;
      case 7:
        room_setup = "lion";
        //vase
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //chair
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //lion
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(3);
        //clock
        clueCoordinates.push_back(13);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
      break;
      case 8:
        room_setup = "barrels";
        //barrels
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        //chairleft
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //table
        clueCoordinates.push_back(6);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(4);
        //chairright
        clueCoordinates.push_back(10);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //candle1
        clueCoordinates.push_back(6);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //candle2
        clueCoordinates.push_back(9);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
      break;
      case 9:
        room_setup = "dungeon";
        //torch1
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //torch2
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //torch3
        clueCoordinates.push_back(14);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //torch4
        clueCoordinates.push_back(14);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //chest
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //cauldron
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //bones
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(10);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //tablechair
        clueCoordinates.push_back(9);
        clueCoordinates.push_back(6);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        //water
        clueCoordinates.push_back(9);
        clueCoordinates.push_back(10);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //bed
        clueCoordinates.push_back(10);
        clueCoordinates.push_back(9);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(2);
      break;
      case 10:
        room_setup = "bedroom";
        //chest
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(8);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //dresser1
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        //dresser2
        clueCoordinates.push_back(10);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(1);
        //bed
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(3);
        //endtable
        clueCoordinates.push_back(10);
        clueCoordinates.push_back(6);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //clock
        clueCoordinates.push_back(13);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(3);
      break;
      case 11:
        room_setup = "wood_bedroom";
        //table
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(3);
        //clock
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //chair
        clueCoordinates.push_back(10);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        //lamp
        clueCoordinates.push_back(10);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);
        //bed
        clueCoordinates.push_back(11);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
        clueCoordinates.push_back(2);
      break;
      case 12:
        room_setup = "bathroom";
        //candle1
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //candle2
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //candle3
        clueCoordinates.push_back(14);
        clueCoordinates.push_back(3);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //candle4
        clueCoordinates.push_back(14);
        clueCoordinates.push_back(7);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(2);
        //water
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(4);
        clueCoordinates.push_back(8);
        clueCoordinates.push_back(5);
        //pail
        clueCoordinates.push_back(12);
        clueCoordinates.push_back(5);
        clueCoordinates.push_back(1);
        clueCoordinates.push_back(1);

      break;
    }
    std::string location = "../resources/roompng/room_" + std::to_string(type) + ".png";
    // std::cout << location << std::endl;
    room_sprite.setTexture(*ResourceManager::getTexture(location));
}

void Room::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // states.transform *= this->getTransform();
    // draw the current sprite
    // target.draw(rect);
    target.draw(room_sprite, states);
    if(isDoor)
      target.draw(rect);
    target.draw(hbox);
}
