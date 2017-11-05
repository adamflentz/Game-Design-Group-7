#include <vector>
#include <iostream>
#include "game/characters/Character.hpp"

void Character::init()
{
    // Make sure player starts inside first room(?)
    // could also make them start inside a random room
    this->setPosition(g->rooms.front()->getPosition().x + 20, g->rooms.front()->getPosition().y + 20);
    // 1p width, height
    // 2p width/2 height
    // 3p, 4p width/2 height/2
    // v.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
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
    hbox = Hitbox(0,16,32,16);
    hbox.follow(this);
    hbox.init();
}

void Character::onUpdate(float dt)
{   
    float speed = 100.0;
    float dx = 0;
    float dy = 0;
    bool noKeyWasPressed = true;
    // TODO: We shouldn't query the keyboard directly here
    //       instead we should use the Joystick class or something
    //       but I haven't figured out the best way for this yet
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        curr = &walk_down;
        dy += speed * dt;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        curr = &walk_up;
        dy += -speed * dt;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        curr = &walk_left;
        dx += -speed * dt;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        curr = &walk_right;
        dx += speed * dt;
        noKeyWasPressed = false;
    }
    // check if inside room 
    if(g->isInsideRoom(sf::FloatRect(hbox.left + dx, hbox.top + dy, hbox.width, hbox.height))){
        this->move(dx, dy);
    };

    curr->play();

    if(noKeyWasPressed)
    {
        curr->stop();
    }
    // update the hitbox
    hbox.onUpdate(dt);
    // update the view
    
    // make the animation go to the next frame
    curr->nextFrame(dt);
}

void Character::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw the room group
    target.draw(*g);
    // draw the animation
    target.draw(*curr, states);
    // draw the hitbox
    target.draw(hbox);
}