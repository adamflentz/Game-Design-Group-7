#include "components/Hitbox.hpp"

void Hitbox::init()
{
    shape.setPosition(this->getPosition());
    shape.setFillColor(sf::Color(0,0,0,0));
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(5);
    shape.setSize(sf::Vector2f(32, 16));
}

void Hitbox::onUpdate(float dt)
{
    if(this->isDebugMode)
        shape.setPosition(this->getPosition());
}

void Hitbox::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    if(this->isDebugMode){
        target.draw(shape);
    }
}