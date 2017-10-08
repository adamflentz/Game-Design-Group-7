#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"
#include "components/SpriteAnimation.hpp"
////////////////
// rando.hpp
//
// This is just a regular character. He has no motivations, goals, or collision checking yet.
// He likes to go for long walks in complete and utter darkness.
// He's very animated.
//
////////////////

class Rando: public GameObject 
{
public:
    void init();
    void onUpdate(float dt);
protected:
    sf::Texture sprite_map;
    SpriteAnimation* curr;
    // create 4 sprite animations representing walking 
    // in the 4 cardinal directions
    SpriteAnimation walk_up;
    SpriteAnimation walk_down;
    SpriteAnimation walk_left;
    SpriteAnimation walk_right;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};