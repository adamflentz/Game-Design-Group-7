#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <mutex>
#include "engine/Engine.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/Hitbox.hpp"
#include "game/rooms/Room.hpp"
#include "game/rooms/RoomGroup.hpp"
#include "components/EntityGroup.hpp"
////////////////
// Character.hpp
//
// This is just a regular character. He has no motivations, goals, or collision checking yet.
// He likes to go for long walks in complete and utter darkness.
// He's very animated.
//
////////////////

class Character: public GameObject 
{
public:
    Character(){};
    void setEntities(EntityGroup* entities){entity_group = entities;};
    /**
    * Stores the room group.
    *   *note*
    *       Having this stored here is dangerous. There's a small possibility that we might
    *       accidentally delete it before the character is done with it. 
    *       We might consider storing a reference to the GameplayScreen (which houses the RoomGroup)
    *       and then "asking" politely for the RoomGroup when we need it.
    */
    void setRoomGroup(RoomGroup* group) { g = group; };

    void setPlayerNumber(int number){player_number = number;};
    /**
    * Captures gamepad events and updates the state of our 
    * character accordingly
    */
    virtual void onGamepadEvent(GamepadEvent e);
    /**
    * Very simple collision checking
    */
    virtual void checkCollisions();

    /* See GameObject Class*/
    virtual void init();
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onUpdate(float dt);
    int player_number = -1;
    // create a hitbox at bottom half of 32x32 character
    Hitbox hbox;
protected:
    int gamepad_index = -1;
    double speed = 120;
    RoomGroup* g;
    EntityGroup* entity_group;
    sf::Vector2f direction;
    sf::Texture sprite_map;
    // The current animation
    SpriteAnimation* curr;
    // create 4 sprite animations representing walking 
    // in the 4 cardinal directions
    SpriteAnimation walk_up;
    SpriteAnimation walk_down;
    SpriteAnimation walk_left;
    SpriteAnimation walk_right;

};

#endif