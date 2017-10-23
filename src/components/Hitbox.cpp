#include "components/Hitbox.hpp"

void Hitbox::init()
{
    offset = sf::Vector2f(this->left, this->top);
    shape.setPosition(this->left, this->top);
    shape.setFillColor(sf::Color(0,0,0,0));
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(5);
    shape.setSize(sf::Vector2f(this->width, this->height));
}

void Hitbox::onUpdate(float dt)
{
    if(this->tracker)
        this->top = tracker->getPosition().y + offset.y;
        this->left = tracker->getPosition().x + offset.x; 
    if(this->isDebugMode)
        shape.setPosition(this->left, this->top);
}

void Hitbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(this->isDebugMode){
        target.draw(shape);
    }
}