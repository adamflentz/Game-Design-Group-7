///////////////////////////
// Hitbox.hpp
//
// A pretty basic hitbox class.
// Hitboxes can be made visibile by setting the debug mode to true.
// Wraps sf::Rect<Float> which has useful methods for 
// checking rectangular intersections as well as point intersections
//
///////////////////////////

#ifndef HITBOXES_HPP
#define HITBOXES_HPP

#include <SFML/Graphics.hpp>
#include "engine/GameObject.hpp"

class Hitbox: public sf::FloatRect, public GameObject
{
public:
    Hitbox(){};
    Hitbox(float x, float y, float w, float h) : sf::FloatRect(x, y, w, h) {};
    void init();
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void onUpdate(float dt);
    void setDebugMode(bool mode) { this->isDebugMode = mode; }
private:
    sf::RectangleShape shape;
    bool isDebugMode = true;
};

#endif