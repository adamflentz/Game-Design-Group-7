#ifndef ROOM_HPP
#define ROOM_HPP

#include "engine/Engine.hpp"
#include <SFML/Graphics.hpp>
#include "components/Hitbox.hpp"

class Room: public GameObject
{
public:
    void init();
    void CreateRoom();
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::RectangleShape rect;
    Hitbox hbox;
protected:
};

#endif
