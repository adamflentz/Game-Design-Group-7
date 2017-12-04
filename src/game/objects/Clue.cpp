#include <vector>
#include <iostream>
#include <string>
#include "game/objects/Clue.hpp"

void Clue::init()
{
    // scroll hardcoded inside first room for now
    int xPos = g->rooms.front()->getPosition().x + (128 - 16);
    int yPos = g->rooms.front()->getPosition().y + (80 - 24);
    this->setPosition(xPos, yPos);

    texture.loadFromFile("../resources/sprites/scroll.png");
    sprite.setTexture(texture);

    hbox = Hitbox(xPos, yPos, 32, 32); // x y w h
    hbox.follow(this);
    hbox.init();
    this->hbox.setColor(sf::Color::Yellow);

    isOpen = false;
}

void Clue::onUpdate(float dt)
{
    hbox.onUpdate(dt);
}

void Clue::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw the sprite
    target.draw(sprite, states);
    // draw the hitbox
    target.draw(hbox);
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
