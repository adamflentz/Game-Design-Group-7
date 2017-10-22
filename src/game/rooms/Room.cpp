#include <vector>
#include "game/rooms/Room.hpp"

void Room::init()
{
    rect.setFillColor(sf::Color::Blue);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(20);
    rect.setSize(sf::Vector2f(620, 380));
}
void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    // draw the current sprite
    target.draw(rect, states);
}

void Room::setRoomPosition(int x, int y)
{
    rect.setPosition(x, y);
}