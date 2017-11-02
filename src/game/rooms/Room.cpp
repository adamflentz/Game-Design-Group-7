#include <vector>
#include "game/rooms/Room.hpp"

void Room::init()
{
    hbox = Hitbox(rect.getPosition().x, rect.getPosition().y, rect.getSize().x, rect.getSize().y);
    hbox.init();
    rect.setFillColor(sf::Color::Blue);
    //rect.setOutlineColor(sf::Color::White);
    //rect.setOutlineThickness(3);
}
void Room::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // states.transform *= this->getTransform();
    // draw the current sprite
    target.draw(rect);
    target.draw(hbox);
}

// void Room::setRoomPosition(int x, int y)
// {
//     rect.setPosition(x, y);
// }
