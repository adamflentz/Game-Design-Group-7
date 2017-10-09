#include "components/Hitbox.hpp"

void Hitbox::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    if(this->isDebugMode){
        target.draw(shape);
    }
}