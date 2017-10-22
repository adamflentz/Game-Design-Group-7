#include <vector>
#include <iostream>
#include "game/characters/rando.hpp"

void Rando::init()
{
    this->setPosition(132, 132);
    // 1p width, height
    // 2p width/2 height
    // 3p, 4p width/2 height/2
    v.reset(sf::FloatRect(0,0,360,480));
    v.setCenter(this->getPosition());
    v.zoom(0.5f);
    v.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    // v.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    // load the sprite map
    sprite_map.loadFromFile("../resources/sprites/rando.png");
    // add animation frames
    std::vector< std::vector<int> > down_frames = { {1}, {2}, {1}, {0} };
    walk_down.setSpriteSheet(sprite_map);
    walk_down.addFrames(down_frames, 32, 32);

    std::vector< std::vector<int> > left_frames = { {4}, {5}, {4}, {3} };
    walk_left.setSpriteSheet(sprite_map);
    walk_left.addFrames(left_frames, 32, 32);

    std::vector< std::vector<int> > right_frames = { {7}, {8}, {7}, {6} };
    walk_right.setSpriteSheet(sprite_map);
    walk_right.addFrames(right_frames, 32, 32);

    std::vector< std::vector<int> > up_frames = { {10}, {11}, {10}, {9} };
    walk_up.setSpriteSheet(sprite_map);
    walk_up.addFrames(up_frames, 32, 32);
    // set default animation
    curr = &walk_down;
    // set the hitbox up to follow this object
    hbox = std::unique_ptr<Hitbox>(new Hitbox(0,16,32,16));
    hbox->follow(this);
    this->addChild(std::move(hbox));
}

void Rando::onUpdate(float dt)
{   
    float speed = 100.0;
    bool noKeyWasPressed = true;
    // TODO: We shouldn't query the keyboard directly here
    //       instead we should use the Joystick class or something
    //       but I haven't figured out the best way for this yet
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        curr = &walk_down;
        this->move(0, speed * dt);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        curr = &walk_up;
        this->move(0, -speed * dt);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        curr = &walk_left;
        this->move(-speed * dt, 0);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        curr = &walk_right;
        this->move(speed * dt, 0);
        noKeyWasPressed = false;
    }
    curr->play();

    if(noKeyWasPressed)
    {
        curr->stop();
    }
    // make the animation go to the next frame
    v.setCenter(this->getPosition());
    curr->nextFrame(dt);
}

void Rando::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw the current sprite
    target.setView(v);
    target.draw(*g);
    target.draw(*curr, states);
}