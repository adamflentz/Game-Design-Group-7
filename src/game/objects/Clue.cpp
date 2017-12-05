#include <vector>
#include <iostream>
#include <string>
#include "game/objects/Clue.hpp"


void Clue::init()
{
    SelectStream(1); // used for random
    int rand = Equilikely(0, 2); //lower and upper bound

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

// void Clue::checkCollisions()
// {
//     this->hbox.setColor(sf::Color::Yellow);
//     std::vector<std::shared_ptr<Character>> entities = entity_group->getCharacters();
//
//     // check proximity to entities
//     //std::cout << entities.size() << std::endl;
//     for(auto it = entities.begin(); it != entities.end(); it++){
//         std::shared_ptr<Character> c = *it;
//         if(c.get() == this)
//             continue;
//         if(this->hbox.intersects(c->hbox)){
//             this->hbox.setColor(sf::Color::Red);
//         }
//     }
// }

void Clue::onUpdate(float dt)
{
    // this->checkCollisions();
    hbox.onUpdate(dt);
}

void Clue::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    target.draw(hbox);
}

//open the clue
void Clue::open()
{
    isOpen = true;
}

//close the clue
void Clue::close()
{
    isOpen = false;
}
