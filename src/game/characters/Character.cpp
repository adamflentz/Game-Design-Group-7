#include <vector>
#include <iostream>
#include <string>
#include <set>
#include "game/characters/Character.hpp"

void Character::init()
{
    this->direction = sf::Vector2f(0,0);
    this->setOrigin(16, 16);
    // Make sure player starts inside first room(?)
    // could also make them start inside a random room
    this->setPosition(g->rooms.front()->getPosition().x + 20 + (32 * player_number), g->rooms.front()->getPosition().y + 20);
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
    // set death sprite
    std::vector< std::vector<int> > death_frame = { {0} };
    death_map.loadFromFile("../resources/sprites/grave.png");
    death_animation.setSpriteSheet(death_map);
    death_animation.addFrames(death_frame, 32, 32);
    // set damage animation
    pain_sprite.loadFromFile("../resources/sprites/blood.png");
    std::vector< std::vector<int> > pain_frame = { {0}, {1}, {2}, {3}, {4}, {5} };
    pain.setSpriteSheet(pain_sprite);
    pain.addFrames(pain_frame, 512, 512);
    ow = &pain;
    ow->stop();
    // set default animation
    curr = &walk_down;
    // Don't automatically play the animation
    curr->stop();
    // set the hitbox up to follow this object
    hbox = Hitbox(-8,0,16,16);
    hbox.follow(this);
    hbox.init();
    health = 3;
    invul = false;
    inPain = false;
}

void Character::onUpdate(float dt)
{
    float dx = this->direction.x * speed * dt;
    float dy = this->direction.y * speed * dt;

    // check if inside any room 
    if(g->isInsideRoom(sf::FloatRect(hbox.left + dx, hbox.top + dy, hbox.width, hbox.height)) && health > 0){  
        this->move(dx, dy);
    };
    if(invul == true && isStarted == false){
        this->clock.restart();
        isStarted = true;
    }
    // std::cout << (int) clock.getElapsedTime().asSeconds() << std::endl;
    if((int)this->clock.getElapsedTime().asSeconds() == 3 && this->invul == true){
        std::cout << "invul removed" << std::endl;
        this->invul = false;
        this->inPain = false;
        isStarted = false;
        
    }
    if(health <= 0){
        curr = &death_animation;
    }

    this->z_index = this->getPosition().y;

    this->checkCollisions();

    // if we're not moving don't animate anything
    if(dx == 0 && dy == 0){
        curr->stop();
    }else{
        curr->play();
    }
    // update the hitbox
    hbox.onUpdate(dt);

    // make the animation go to the next frame
    curr->nextFrame(dt);
}

void Character::checkCollisions()
{
    this->hbox.setColor(sf::Color::Yellow);
    std::vector<std::shared_ptr<Character>> entities = entity_group->getCharacters();
    // // check proximity to other entities or whatever
    // std::cout << entities.size() << std::endl;
    for(auto it = entities.begin(); it != entities.end(); it++){
        std::shared_ptr<Character> c = *it;
        if(c.get() == this)
            continue;
        if(this->hbox.intersects(c->hbox)){
            this->hbox.setColor(sf::Color::Red);
        }
    }
}

void Character::hurt(){
    this->health--;
    inPain = true;
    ow = &pain;
}

/**
* Draws the characters
*/
void Character::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(inPain == true){
        target.draw(*ow, states);
    }
    // draw the animation
    target.draw(*curr, states);
    // draw the hitbox
    target.draw(hbox);
}

void Character::onGamepadEvent(GamepadEvent e)
{
    if(health > 0){
        switch(e.type){
            case GamepadEvent::TYPE::RELEASED:
                // in c++ you can't switch/case a string
                if(e.button == "UP" || e.button == "DOWN")
                    this->direction.y = 0;
                else if(e.button == "LEFT" || e.button == "RIGHT")
                    this->direction.x = 0;
                else if(e.button == "X") // stop running
                    this->speed /= 2;

                if(this->direction.y <= -1) {
                    curr = &walk_up;
                }
                if(this->direction.y >= 1) {
                    curr = &walk_down;
                }
                if(this->direction.x <= -1) {
                    curr = &walk_left;
                }
                if(this->direction.x >= 1) {
                    curr = &walk_right;
                }
                break;
            case GamepadEvent::TYPE::PRESSED:
                if(e.button == "UP"){
                    // check if a y velocity
                    curr = &walk_up;
                    this->direction.y = -1;
                }
                if(e.button == "DOWN"){
                    curr = &walk_down;
                    this->direction.y = 1;
                }
                if(e.button == "LEFT"){
                    curr = &walk_left;
                    this->direction.x = -1;
                }
                if(e.button == "RIGHT"){
                    curr = &walk_right;
                    this->direction.x = 1;
                }
                if(e.button == "X"){ // run
                    this->speed *= 2;
                }


                break;
        }
    }
}
