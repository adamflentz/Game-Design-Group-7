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
    sf::Sprite room_sprite;
    sf::Texture roomTexture;
    Hitbox hbox;
    void setRoomType(int type);
    int  getRoomType(int type) { return room_type; };
    bool isDoor = false;
    bool isBottom = false;
protected:
    int room_type;
};

#endif
