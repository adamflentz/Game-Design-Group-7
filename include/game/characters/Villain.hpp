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
// #include "game/resources/EntityGroup.hpp"
#include "game/characters/Character.hpp"
////////////////
// Villain.hpp
//
// This is a generic ghost.  He wants to hunt and kill the other character
// present in the game.  He wanders the house looking for them, chases and attacks when
// a character is seen, and then wanders once again.
//
////////////////

class Villain: public Character
{
public:
    void init();
    void onUpdate(float dt);
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void wander();
    void chase();
    void returnToCenter();
    void setDirection();
    void hurt();
    bool checkCharacters();
    bool isVillain(){return true;};
protected:
    int randint;
    int health;
    std:: string previousString;
    std::vector<std::string> possiblerooms;
    int roomCenterX;
    int roomCenterY;
    float previousLocationX;
    float previousLocationY;
    bool isChasing;
    bool started;
    bool needsCentering;
    bool fastSpeed;
    sf::FloatRect roomHbox;
    sf::FloatRect chaseHbox;
    sf::Sound ghost_sound;

};

#endif
