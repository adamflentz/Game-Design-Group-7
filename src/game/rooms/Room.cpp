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
    std::string location = "../resources/roompng/room_" + std::to_string(type) + ".png";
    std::cout << location << std::endl;
    room_sprite.setTexture(*ResourceManager::getTexture(location));
    // room_sprite.setPosition(-25, -25);
    // room_sprite.setScale(1.1, 1.1);
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
