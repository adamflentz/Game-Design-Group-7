#ifndef CLUES_HPP
#define CLUES_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"
#include "engine/ClueReader.hpp"
#include "components/Hitbox.hpp"
#include "game/rooms/Room.hpp"
#include "game/rooms/RoomGroup.hpp"
#include "components/EntityGroup.hpp"

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
    void setCoordinates(int x, int y, int w, int h);
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void open();
    void close();
    void onGamepadEvent(GamepadEvent e);
    void setRoomGroup(RoomGroup* group) { g = group; };
    void setEntities(EntityGroup* entities){entity_group = entities;};
    void checkCollisions();
    void setClueNumber(int number){clue_number = number;};
    Hitbox hbox;

    // the written information for the player
    std::string clueSpec;
    std::string clueVague;
    std::string clueWorthless;
    int clue_number = -1;

protected:
    int xPos;
    int yPos;
    int width;
    int height;
    RoomGroup* g;
    EntityGroup* entity_group;
    sf::Sprite sprite;
    sf::Texture texture;
    bool isOpen;
    int clueNum;
};

#endif
