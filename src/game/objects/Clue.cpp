#include <vector>
#include <iostream>
#include <string>
#include "game/objects/Clue.hpp"

void Clue::init()
{
    // scroll hardcoded inside first room for now
    this->setPosition(g->rooms.front()->getPosition().x + (128 - 16), g->rooms.front()->getPosition().y + (80 - 24));
    // load the texture
    texture.loadFromFile("../resources/sprites/scroll.png");
    sprite.setTexture(texture);

    // set the hitbox up to follow this object
    hbox = Hitbox(0,16,32,16); // x y w h
    hbox.follow(this);
    hbox.init();

    isOpen = false;
}

void Clue::onUpdate(float dt)
{

}

void Clue::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw the sprite
    target.draw(sprite, states);
    // draw the hitbox
    target.draw(hbox, states);
}

//open the clue
void Clue::open()
{

}

//close the clue
void Clue::close()
{

}

void Clue::onGamepadEvent(GamepadEvent e)
{
    if (GamepadEvent::TYPE::RELEASED && e.button == "B") {
        if (isOpen == false) {
            open();
        } else {
            close();
        }
    }
}
