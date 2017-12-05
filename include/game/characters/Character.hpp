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
    void setCharacter(Config::CHARACTER c){ character = c; };
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
    void setGamepadIndex(int number){gamepad_index = number;};
    int  getGamepadIndex(){ return gamepad_index; };
    /**
    * Captures gamepad events and updates the state of our
    * character accordingly
    */
    virtual void onGamepadEvent(GamepadEvent e);
    /**
    * Very simple collision checking
    */
    virtual void checkCollisions();
    /**
     * Rewriteable hurt method to be used by ghost and char
     */
    virtual void hurt();

    /* See GameObject Class*/
    virtual void init();
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onUpdate(float dt);
    int player_number = -1;
    // create a hitbox at bottom half of 32x32 character
    Hitbox hbox;
    Hitbox hurtbox; // hurtbox for the sword(?)
    int health;
    int maxHealth;
    bool invul;
    void checkClues();
    void checkVillain();
    void attack();
    virtual bool isVillain(){return false;};
    bool readClue = false;
    bool atClue = false;
    std::shared_ptr<Clue> currentClue;
<<<<<<< HEAD
    // Base attributes
=======
    sf::Vector2f direction;
    Config::CHARACTER character;

protected:
    int gamepad_index = -1;

    // Base attributes 
>>>>>>> bdf4933ecc23c111a44fbdf9c22f3ebef5117c2e
    double speed = 120;
    double stealth = 100;
    double strength = 100;
    double intelligence = 100;
    RoomGroup* g;
    EntityGroup* entity_group;
    sf::Texture sprite_map;
    sf::Texture death_map;
    sf::Texture pain_sprite;
    sf::Sound chara_hurt;
    sf::Sound chara_death;
    // An attack animation
    SpriteAnimation attack_anim;
    // The current animation
    SpriteAnimation* curr;
    SpriteAnimation* ow;
    // create 4 sprite animations representing walking
    // in the 4 cardinal directions
    SpriteAnimation walk_up;
    SpriteAnimation walk_down;
    SpriteAnimation walk_left;
    SpriteAnimation walk_right;
    bool stopUp;
    bool stopDown;
    bool stopLeft;
    bool stopRight;
    SpriteAnimation death_animation;
    sf::Clock clock;
    bool isStarted;
    bool panic;
    bool isAlive = true;
    bool isAttacking = false;


};

#endif
