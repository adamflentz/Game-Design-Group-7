#include <vector>
#include <iostream>
#include <string>
#include <set>
#include "game/characters/Character.hpp"
#include "game/characters/Villain.hpp"

void Character::init()
{
    chara_hurt.setBuffer(*ResourceManager::getSoundBuffer("../resources/music/hurt.wav"));
    chara_death.setBuffer(*ResourceManager::getSoundBuffer("../resources/music/dead.wav"));
    chara_death.play();
    this->direction = sf::Vector2f(0,0);
    this->setOrigin(16, 16);
    int sprite_location = -1;
    std::cout << "Player Number: " << this->player_number << " is Character ";
    switch(character){
        case Config::CHARACTER::MOM:
            std::cout << "Mom" << std::endl;
            // ++ intelligence
            // -- speed
            // intelligence *= 2;
            // speed /= 1.2;
            health = 3;
            maxHealth = 3;
            sprite_location = 0;
            break;
        case Config::CHARACTER::SIS:
            std::cout << "SIS" << std::endl;
            // ++ stealth
            // -- strength
            health = 3;
            maxHealth = 3;

            sprite_location = 1;
            // stealth *= 2;
            // strength /= 2;
            break;
        case Config::CHARACTER::BRO:
            std::cout << "BRO" << std::endl;
            // ++ speed
            // -- stealth
            health = 3;
            maxHealth = 3;
            sprite_location = 2;
            // speed *= 1.3;
            // stealth /= 2;
            break;
        case Config::CHARACTER::DAD:
            std::cout << "DAD" << std::endl;
            health = 5;
            maxHealth = 5;
            sprite_location = 3;
            break;
    }
    // int sprite_location = static_cast<int>(character);
    int x = ((sprite_location) % 2);
    int y = ((sprite_location) / 2);
    int mod = 3 * x + 24 * y;

    std::cout << x << " " << y << std::endl;

    // Make sure player starts inside first room(?)
    // could also make them start inside a random room

    this->setPosition(
      g->getRoom(0)->hbox.left + 20 + (32 * player_number),
      g->getRoom(0)->hbox.top + 20);

    attack_anim.setSpriteSheet(*ResourceManager::getTexture("../resources/sprites/swipe.png"));
    attack_anim.setPosition(16, 0);
    std::vector< std::vector<int> > swipe_frames = {
        {0}, {1}, {2}, {3}
    };
    attack_anim.addFrames(swipe_frames, 32, 32);

    if(g->getRoom(0)->room_setup == "armory"){
        this->setPosition(
            g->getRoom(0)->hbox.left + 20 + (32 * player_number),
            g->getRoom(0)->hbox.top + 160);
    }
    else if(g->getRoom(0)->room_setup == "throne"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 160);
    }
    else if(g->getRoom(0)->room_setup == "grave"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 128);
    }
    else if(g->getRoom(0)->room_setup == "parlor"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 128);
    }
    else if(g->getRoom(0)->room_setup == "lounge"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 160);
    }
    else if(g->getRoom(0)->room_setup == "kitchen"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 160);
    }
    else if(g->getRoom(0)->room_setup == "lion"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 160);
    }
    else if(g->getRoom(0)->room_setup == "barrels"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 160);
    }
    else if(g->getRoom(0)->room_setup == "dungeon"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 256);
    }
    else if(g->getRoom(0)->room_setup == "bedroom"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 160);
    }
    else if(g->getRoom(0)->room_setup == "wood_bedroom"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 128);
    }
    else if(g->getRoom(0)->room_setup == "bathroom"){
        this->setPosition(
        g->getRoom(0)->hbox.left + 20 + (32 * player_number),
        g->getRoom(0)->hbox.top + 96);
    }
    // this->setPosition(g->rooms.front()->getPosition().x + 20 + (32 * player_number), g->rooms.front()->getPosition().y + 20);
    // 1p width, height
    // 2p width/2 height
    // 3p, 4p width/2 height/2
    // v.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    // v.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    // load the sprite map
    sprite_map.loadFromFile("../resources/sprites/character_sheet.png");
    // add animation frames
    std::vector< std::vector<int> > down_frames = {
        {mod +  1}, {mod + 2}, {mod + 1}, { mod + 0}
    };
    walk_down.setSpriteSheet(sprite_map);
    walk_down.addFrames(down_frames, 32, 32);

    std::vector< std::vector<int> > left_frames = {
        {7 + mod}, {8 + mod}, {7 + mod}, {6 + mod}
    };
    walk_left.setSpriteSheet(sprite_map);
    walk_left.addFrames(left_frames, 32, 32);

    std::vector< std::vector<int> > right_frames = {
        {13 + mod}, {14 + mod}, {13 + mod}, {12 + mod}
    };
    walk_right.setSpriteSheet(sprite_map);
    walk_right.addFrames(right_frames, 32, 32);

    std::vector< std::vector<int> > up_frames = {
        {19 + mod}, {20 + mod}, {19 + mod}, {18 + mod}
    };
    walk_up.setSpriteSheet(sprite_map);
    walk_up.addFrames(up_frames, 32, 32);
    // set death sprite
    std::vector< std::vector<int> > death_frame = { {0} };
    death_map.loadFromFile("../resources/sprites/grave.png");
    death_animation.setSpriteSheet(death_map);
    death_animation.addFrames(death_frame, 32, 32);
    // set damage animation
    // set default animation
    curr = &walk_down;
    // Don't automatically play the animation
    curr->stop();
    // set the hitbox up to follow this object
    hbox = Hitbox(-8,0,16,16);
    hbox.follow(this);
    hbox.init();
    invul = false;
}
void Character::checkVillain(){
    std::vector<std::shared_ptr<Character>> entities = entity_group->getCharacters();
    for(auto it = entities.begin(); it != entities.end(); it++){
        std::shared_ptr<Character> c = *it;
        // std::cout << this->hbox.left + this->hbox.width + 32;
        // std::cout << " ";
        if(c->isVillain() == true){
            if((c->hbox) == this->hbox){continue;}
            // std::cout << c->hbox.left << std::endl;
            if(curr == &walk_right && this->hbox.left + this->hbox.width + 32 > c->hbox.left && this->hbox.left + this->hbox.width < c->hbox.left &&
            c->hbox.top >= this->hbox.top - 20 && c->hbox.top <= this->hbox.top + 36){
                std::cout << "hiyah" << std::endl;
                c->hurt();
            }
            if(curr == &walk_left && this->hbox.left - 32 < c->hbox.left + c->hbox.width &&
                c->hbox.top >= this->hbox.top - 20 && c->hbox.top <= this->hbox.top + 36){
                std::cout << "hiyah" << std::endl;
                c->hurt();
            }
            if(curr == &walk_up && this->hbox.top + this->hbox.height + 32 > c->hbox.height &&
            c->hbox.left >= this->hbox.left - 20 && c->hbox.top <= this->hbox.left + 36){
                std::cout << "hiyah" << std::endl;
                c->hurt();
             }
            if(curr == &walk_down && this->hbox.top - 32 < c->hbox.top + c->hbox.height &&
                c->hbox.left >= this->hbox.left - 20 && c->hbox.top <= this->hbox.left + 36){
                std::cout << "hiyah" << std::endl;
                c->hurt();
            }
            // std::cout << c->health << std::endl;
        }
    }
}
void Character::checkClues(){
    std::vector<std::shared_ptr<Clue>> entities = entity_group->getClues();
    // std::cout << entities.size() << std::endl;
    for(auto it = entities.begin(); it != entities.end(); it++){
        std::shared_ptr<Clue> c = *it;

        if(c->hbox.intersects(this->hbox)){
            // std::cout << c->hbox.top + c->hbox.height - this->hbox.top << std::endl;
            if(this->hbox.left + this->hbox.width - c->hbox.left >= 0 && this->hbox.left + this->hbox.width - c->hbox.left <= 4){
                this->stopRight = true;
                // std::cout << "stop right" << std::endl;
            }
            else if(c->hbox.left + c->hbox.width - this->hbox.left >= 0 && c->hbox.left + c->hbox.width - this->hbox.left <= 4){
                this->stopLeft = true;
                // std::cout << "stop left" << std::endl;
            }
            else if(c->hbox.top + c->hbox.height - this->hbox.top >= 0 && c->hbox.top + c->hbox.height - this->hbox.top <= 4){
                this->stopUp = true;
                // std::cout << "stop up" << std::endl;
            }
            else if(this->hbox.top + this->hbox.height - c->hbox.top >= 0 && this->hbox.top + this->hbox.height - c->hbox.top <= 4){
                this->stopDown = true;
                // std::cout << "stop down" << std::endl;
            }
            this->currentClue = c;
            this->hbox.setColor(sf::Color::Green);
            atClue = true;
            break;
        }
        else{
            this->stopLeft = false;
            this->stopRight = false;
            this->stopUp = false;
            this->stopDown = false;
            this->currentClue = NULL;
            atClue = false;
            // std::cout << "in the else " << readClue << std::endl;
        }
    }
}

void Character::onUpdate(float dt)
{
    float dx = this->direction.x * speed * dt;
    float dy = this->direction.y * speed * dt;

    // check if inside any room
    if(g->isInsideRoom(sf::FloatRect(hbox.left + dx, hbox.top + dy, hbox.width, hbox.height)) && health > 0){
        this->checkClues();
        if(this->stopLeft == true && dx < 0){
            dx = 0;
        }
        if(this->stopRight == true && dx > 0){
            dx = 0;
        }
        if(this->stopUp == true && dy < 0){
            dy = 0;
        }
        if(this->stopDown == true && dy > 0){
            dy = 0;
        }
        this->move(dx, dy);
    };
    if(invul == true && isStarted == false){
        this->clock.restart();
        isStarted = true;
    }

    // std::cout << (int) clock.getElapsedTime().asSeconds() << std::endl;
    if(this->clock.getElapsedTime().asSeconds() >= 3 && this->invul == true){
        std::cout << "invul removed" << std::endl;
        this->invul = false;
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
    // Update attacking animation
    if(isAttacking){
        attack_anim.nextFrame(dt);
    }
    // make the animation go to the next frame
    curr->nextFrame(dt);
}

void Character::checkCollisions()
{
    this->hbox.setColor(sf::Color::Yellow);
    std::vector<std::shared_ptr<Character>> entities = entity_group->getCharacters();
    // // check proximity to other entities or whatever
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
    this->invul = true;
    if(health > 0){
        chara_hurt.play();
    }
    else{
        std::cout << "should play death" << std::endl;
        chara_death.stop();
        chara_death.play();
    }
}

void Character::attack(){
    if(!(this->isAttacking)){
        this->isAttacking = true;
        attack_anim.play([=](){
            // std::cout << "Attack done" << std::endl;
            attack_anim.stop();
            this->isAttacking = false;
        });
        this->checkVillain();
    }
}

/**
* Draws the characters
*/
void Character::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(isAttacking)
        target.draw(attack_anim, states);
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
                if((e.button == "UP") || (e.button == "DOWN"))
                    this->direction.y = 0;
                else if((e.button == "LEFT") || (e.button == "RIGHT"))
                    this->direction.x = 0;
                else if(e.button == "X"){
                    if(character == Config::CHARACTER::BRO){
                        // stop running
                        this->speed /= 2;
                    }
                }
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
                    if(stopUp == false){
                        attack_anim.setRotation(-90);
                        attack_anim.setPosition(0, 16);
                        this->direction.y = -1;
                    }
                    else{
                        this->direction.y = 0;
                    }

                }
                if(e.button == "DOWN"){
                    curr = &walk_down;
                    if(stopDown == false){
                        attack_anim.setRotation(90);
                        attack_anim.setPosition(32, 16);
                        this->direction.y = 1;
                    }
                    else{
                        this->direction.y = 0;
                    }
                }
                if(e.button == "LEFT"){
                    curr = &walk_left;
                    if(stopLeft == false){
                        attack_anim.setRotation(180);
                        attack_anim.setPosition(16, 32);
                        this->direction.x = -1;
                    }
                    else{
                        this->direction.x = 0;
                    }
                }
                if(e.button == "RIGHT"){
                    curr = &walk_right;
                    if(stopRight == false){
                        attack_anim.setRotation(0);
                        attack_anim.setPosition(16, 0);
                        this->direction.x = 1;
                    }
                    else{
                        this->direction.x = 0;
                    }
                }

                if(e.button == "B"){
                    this->attack();
                }

                if(e.button == "X"){ // run
                    if(character == Config::CHARACTER::BRO){
                        this->speed *= 2;
                    }
                }

                if(e.button == "A"){ // perform an action
                    std::cout << this->currentClue << std::endl;
                    if(readClue == false){
                        readClue = true; // open clue
                    }
                    else if(readClue == true){
                        readClue = false; // close clue
                    }
                }

                break;
        }
    }
}
