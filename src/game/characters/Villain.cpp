#include <vector>
#include <iostream>
#include <string>
#include <set>
#include "game/characters/Villain.hpp"

void Villain::init()
{
    ghost_sound.setBuffer(*ResourceManager::getSoundBuffer("../resources/music/near.flac"));
    // Make sure player starts inside first room(?)
    // could also make them start inside a random room
    this->setPosition(g->rooms.front()->getPosition().x + ((512 / 2) - 16), g->rooms.front()->getPosition().y + ((384 / 2) - 24));

    // load the sprite map
    sprite_map.loadFromFile("../resources/sprites/ghost.png");
    // add animation frames
    std::vector< std::vector<int> > down_frames = { {1}, {2}, {1}, {0} };
    walk_down.setSpriteSheet(sprite_map);
    walk_down.addFrames(down_frames, 32, 48);

    std::vector< std::vector<int> > left_frames = { {4}, {5}, {4}, {3} };
    walk_left.setSpriteSheet(sprite_map);
    walk_left.addFrames(left_frames, 32, 48);

    std::vector< std::vector<int> > right_frames = { {7}, {8}, {7}, {6} };
    walk_right.setSpriteSheet(sprite_map);
    walk_right.addFrames(right_frames, 32, 48);

    std::vector< std::vector<int> > up_frames = { {10}, {11}, {10}, {9} };
    walk_up.setSpriteSheet(sprite_map);
    walk_up.addFrames(up_frames, 32, 48);
    // Don't automatically play the animation

    curr = &walk_down;
    curr->stop();
    // Death tombstone

    std::vector< std::vector<int> > death_frame = { {0} };
    death_map.loadFromFile("../resources/sprites/grave.png");
    death_animation.setSpriteSheet(death_map);
    death_animation.addFrames(death_frame, 32, 32);
    // set the hitbox up to follow this object

    hbox = Hitbox(0,16,32,16);
    hbox.follow(this);
    hbox.init();
    health = 25;
}

void Villain::onUpdate(float dt)
{
    // std::cout << health << std::endl;
    roomHbox = g->getRoom(this->hbox);
    this->checkCharacters();
    this->checkDistance();
    this->chase();

    // std::cout << this->getPosition().x << std::endl;
    int dx = this->direction.x * speed * dt;
    int dy = this->direction.y * speed * dt;

    this->z_index = this->getPosition().y + 20;

    // check for collisions
    this->checkCollisions();
    if(health <= 0){
        curr = &death_animation;
    }

    //started = true;
    if(health > 0){
        this->move(dx, dy);
    }

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

void Villain::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw the animation
    target.draw(*curr, states);
    // draw the hitbox
    target.draw(hbox);
}

void Villain::checkCharacters(){

    std::vector<std::shared_ptr<Character>> entities = entity_group->getCharacters();
    roomHbox = g->getRoom(this->hbox);
    for(auto it = entities.begin(); it != entities.end(); it++){
        std::shared_ptr<Character> c = *it;
        if(c.get() == this)
            continue;
        // if(c->character == Config::CHARACTER::SIS && c->direction.x == 0 && c->direction.y == 0){
        //     continue;
        // }
        if(c->health > 0){
            this->hbox.setColor(sf::Color::Green);
            this->chaseHbox = c->hbox;
        }
    }
}

void Villain::hurt(){
  std::cout << "4" << std::endl;
    health--;
    this->randint = rand() % this->g->rooms.size();
    int count = 0;
    std::cout << randint << std::endl;
    for(auto rmit = g->rooms.begin(); rmit != g->rooms.end(); rmit++){
        if(count == randint){
            if((*rmit)->hbox == g->getRoom(this->hbox) || (*rmit)->isDoor == true){
                this->randint = rand() % this->g->rooms.size();
                rmit = g->rooms.begin();
                count = 0;
            }
            else{
                if(health > 0){
                    std::cout << "escape" << std::endl;
                    this->setPosition((*rmit)->hbox.left + (448 / 2) - 16, (*rmit)->hbox.top   + (288 / 2) - 36);

                    break;
                }
            }
        }
        count++;
    }
}


void Villain::chase()
{
    if(this->chaseHbox.left < this->hbox.left){
        this->direction.x = -1;
        //curr = &walk_left;
    }
    if(this->chaseHbox.left  > this->hbox.left) {
        this->direction.x = 1;
        //curr = &walk_right;
    }
    if(this->chaseHbox.top  > this->hbox.top){
        this->direction.y = 1;
        curr = &walk_down;
    }
    if(this->chaseHbox.top < this->hbox.top){
        this->direction.y = -1;
        curr = &walk_up;
    }

    // if ((this->chaseHbox.top < this->hbox.top)&&(this->chaseHbox.top+50 > this->hbox.top)) {
    //     if(this->chaseHbox.left < this->hbox.left){
    //         this->direction.y = 0;
    //         this->direction.x = -1;
    //         curr = &walk_left;
    //     }
    //     if(this->chaseHbox.left > this->hbox.left) {
    //         this->direction.y = 0;
    //         this->direction.x = 1;
    //         curr = &walk_right;
    //     }
    // }
    //
    // if ((this->chaseHbox.left < this->hbox.left)&&(this->chaseHbox.left+50 > this->hbox.left)) {
    //     if(this->chaseHbox.top > this->hbox.top){
    //         this->direction.x = 0;
    //         this->direction.y = 1;
    //         curr = &walk_down;
    //     }
    //     if(this->chaseHbox.top < this->hbox.top){
    //         this->direction.x = 0;
    //         this->direction.y = -1;
    //         curr = &walk_up;
    //     }
    // }
    //
    // else {
    //     if(this->chaseHbox.left < this->hbox.left){
    //         this->direction.x = -1;
    //         curr = &walk_left;
    //     }
    //     if(this->chaseHbox.left > this->hbox.left) {
    //         this->direction.x = 1;
    //         curr = &walk_right;
    //     }
    //     if(this->chaseHbox.top > this->hbox.top){
    //         this->direction.y = 1;
    //         curr = &walk_down;
    //     }
    //     if(this->chaseHbox.top < this->hbox.top){
    //         this->direction.y = -1;
    //         curr = &walk_up;
    //     }
    // }
}

void Villain::checkDistance() {
    //std::cout << distance << std::endl;
    //std::cout << speed << std::endl;
    distance = sqrt(pow(this->chaseHbox.left - this->hbox.left, 2) + pow(this->chaseHbox.top - this->hbox.top, 2));
    if (distance <= 300) {
      speed = 105;
      if (distance >= 299 && distance >= 298 && gettingCloser(distance)) {
          ghost_sound.play();}
    }

    else if (distance >= 300 && distance <= 600) {
      speed = 181;
    }

    else {
      speed = 500;
    }
}

bool Villain::gettingCloser(float d) {
    float d1 = d;
    float d2;
    if (clock.getElapsedTime().asSeconds() >= 500){
        float d2 = d;
    }
    if (d1 - d2 > 0) {
        clock.restart();
        return true;
    }
    clock.restart();
    return false;
}
