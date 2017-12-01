#ifndef VILLAIN_HPP
#define VILLAIN_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/Hitbox.hpp"
#include "game/rooms/Room.hpp"
#include "game/rooms/RoomGroup.hpp"
#include "game/resources/EntityGroup.hpp"
////////////////
// Villain.hpp
//
// This is a generic ghost.  He wants to hunt and kill the other character
// present in the game.  He wanders the house looking for them, chases and attacks when 
// a character is seen, and then wanders once again.
//
////////////////

class Villain: public GameObject 
{
public:
    void init();
    void onUpdate(float dt);
    void setGroup(RoomGroup* group) { g = group; };
    void setEntities(EntityGroup* entities) {e = entities;};
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void wander();
    void setDirection();
protected:
    int randint;
    std:: string previousString;
    std::vector<std::string> possiblerooms;
    RoomGroup* g;
    EntityGroup* e;
    double speed = 120;
    sf::Vector2f direction;
    int roomCenterX;
    int roomCenterY;
    float previousLocationX;
    float previousLocationY;
    sf::Texture sprite_map;
    SpriteAnimation* curr;
    // create 4 sprite animations representing walking 
    // in the 4 cardinal directions
    SpriteAnimation walk_up;
    SpriteAnimation walk_down;
    SpriteAnimation walk_left;
    SpriteAnimation walk_right;
    // create a hitbox at bottom half of 32x32 character
    Hitbox hbox;
    
};

#endif