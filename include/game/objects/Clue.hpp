#ifndef CLUES_HPP
#define CLUES_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"
#include "engine/ClueReader.hpp"
#include "components/Hitbox.hpp"
#include "game/rooms/Room.hpp"
#include "game/rooms/RoomGroup.hpp"

////////////////
// Clues.hpp
//
//
////////////////

class Clue: public GameObject
{
public:
    void init();
    void onUpdate(float dt);
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void open();
    void close();
    void onGamepadEvent(GamepadEvent e);
    void setRoomGroup(RoomGroup* group) { g = group; };
    Hitbox hbox;

protected:
    RoomGroup* g;
    sf::Sprite sprite;
    sf::Texture texture;
    bool isOpen;
};

#endif
