#include <vector>
#include <iostream>
#include <string>
#include "game/characters/Villain.hpp"

void Villain::init()
{
    this->direction = sf::Vector2f(0,0);
    // Make sure player starts inside first room(?)
    // could also make them start inside a random room
    this->setPosition(g->rooms.front()->getPosition().x + (128 - 16), g->rooms.front()->getPosition().y + (80 - 24));
    this->setDirection();
    // 1p width, height
    // 2p width/2 height
    // 3p, 4p width/2 height/2
    // v.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    // v.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
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
    curr->stop();
    // set the hitbox up to follow this object
    hbox = Hitbox(0,16,32,16);
    hbox.follow(this);
    hbox.init();
    isChasing = false;
    needsCentering = false;
    fastSpeed = false;
}

void Villain::onUpdate(float dt)
{
    roomHbox = g->getRoom(this->hbox);
    // std::cout << this->getPosition().x << std::endl;
    // std::cout << roomHbox.left + (256 / 2) - 16 << std::endl;
    int dx = this->direction.x * speed * dt;
    int dy = this->direction.y * speed * dt;
    // check if characters are inside room with monster
    if(this->checkCharacters() == false){
        if(isChasing == true && (this->getPosition().x != roomHbox.left + (256 / 2) - 16 || this->getPosition().y != (roomHbox.top + (160 / 2) - 24))){
            this->returnToCenter();
            // std::cout << "centering" << std::endl;
        }
        else{
            this->wander();
            // std::cout << "wandering" << std::endl;
        }
    }
    else{
        if(fastSpeed == false){
            speed *= 1.5;
            fastSpeed = true;
        }
        isChasing = true;
        this->chase();
        // std::cout << "CHASING" << std::endl;
    }
    // Set z index
    this->z_index = this->getPosition().y + 20;

    // check for collisions
    this->checkCollisions();

    started = true;
    this->move(dx, dy);
    // check if inside room
    // if(g->isInsideRoom(sf::FloatRect(hbox.left + dx, hbox.top + dy, hbox.width, hbox.height))){
    //
    //
    //}
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
bool Villain::checkCharacters(){
    std::vector<std::shared_ptr<Character>> entities = entity_group->getCharacters();
    roomHbox = g->getRoom(this->hbox);
    for(auto it = entities.begin(); it != entities.end(); it++){
        std::shared_ptr<Character> c = *it;
        if(c.get() == this)
            continue;
        if(c->hbox.intersects(roomHbox) && c->health > 0 && c->invul == false){
            this->hbox.setColor(sf::Color::Green);
            this->chaseHbox = c->hbox;
            return true;
        }
        return false;
    }

}
void Villain::returnToCenter(){
    if(fastSpeed == true){
        speed /= 1.5;
        fastSpeed = false;
    }
    int xloc = this->getPosition().x;
    int yloc = this->getPosition().y;
    roomHbox = g->getRoom(this->hbox);
    // std::cout << roomHbox.left << std::endl;
    if(xloc < roomHbox.left + (256 / 2) - 16){
        this->direction.x = 1;
        curr = &walk_right;
    }
    else if(xloc > roomHbox.left + (256 / 2) - 16){
        this->direction.x = -1;
        curr = &walk_left;
    }
    else{
        this->direction.x = 0;
    }
    if(yloc > roomHbox.top + (160 / 2) - 24){
        this->direction.y = -1;
        curr = &walk_up;
    }
    else if(yloc < roomHbox.top + (160 / 2) - 24){
        this->direction.y = 1;
        curr = &walk_down;
    }
    else{
        this->direction.y = 0;
    }
    if(this->getPosition().x == roomHbox.left + (256 / 2) - 16 - 1){
        this->setPosition(this->getPosition().x + 1, this->getPosition().y);


        this->direction.x = 0;
    }
    if(this->getPosition().x == roomHbox.left + (256 / 2) - 16 + 1){
        this->setPosition(this->getPosition().x - 1, this->getPosition().y);


        this->direction.x = 0;
    }
    if(this->getPosition().y == roomHbox.top + (160 / 2) - 24 - 1){
        this->setPosition(this->getPosition().x, this->getPosition().y + 1);
        this->direction.y = 0;
    }
    if(this->getPosition().y == roomHbox.top + (160 / 2) - 24 + 1){
        this->setPosition(this->getPosition().x, this->getPosition().y - 1);


        this->direction.y = 0;
    }
    if((this->getPosition().y == roomHbox.top + (160 / 2) - 24) && (this->getPosition().x == roomHbox.left + (256 / 2) - 16)){
        this->setDirection();
        // std::cout << "centered" << std::endl;
        needsCentering = false;
        isChasing = false;
    }
}
void Villain::chase()
{
    needsCentering = true;
    // std::cout << this->chaseHbox.top << std::endl;
    if(this->chaseHbox.left < this->hbox.left - 10){
        this->direction.x = -1;
        curr = &walk_left;
    }
    if(this->chaseHbox.left > this->hbox.left + 10){
        this->direction.x = 1;
        curr = &walk_right;
    }
    if(this->chaseHbox.top > this->hbox.top + 10){
        this->direction.y = 1;
        curr = &walk_down;
    }
    if(this->chaseHbox.top < this->hbox.top - 10){
        this->direction.y = -1;
        curr = &walk_up;
    }
    std::vector<std::shared_ptr<Character>> entities = entity_group->getCharacters();
    for(auto it = entities.begin(); it != entities.end(); it++){
        std::shared_ptr<Character> c = *it;
        if(c.get() == this)
            continue;
        if(this->hbox.intersects(c->hbox) && c->invul == false && c->health > 0){
            c->hurt();
            this->randint = rand() % this->g->rooms.size();
            int count = 0;
            std::cout << g->rooms.size() << std::endl;
            for(auto rmit = g->rooms.begin(); rmit != g->rooms.end(); rmit++){
                if(count == randint){
                    if((*rmit)->hbox == g->getRoom(this->hbox)){
                        this->randint = rand() % this->g->rooms.size();
                    }
                    else{
                        if(fastSpeed == true){
                            speed /= 1.5;
                            fastSpeed = false;
                        }
                        this->setPosition((*rmit)->hbox.left + (256/2) - 16, (*rmit)->hbox.top   + (160 / 2) - 24);
                        this->setDirection();
                        break;
                    }
                }
                count++;
            }

        }
    }



}
void Villain::wander()
{
    int xloc = this->getPosition().x;
    int yloc = this->getPosition().y;
    if(needsCentering == true){
        if(this->getPosition().x == roomHbox.left + (256 / 2) - 16 - 1){
            this->setPosition(this->getPosition().x + 1, this->getPosition().y);
            // std::cout << "correct" << std::endl;
            needsCentering = false;
            this->setDirection();
        }
        if(this->getPosition().x == roomHbox.left + (256 / 2) - 16 + 1){
            this->setPosition(this->getPosition().x - 1, this->getPosition().y);
            // std::cout << "correct" << std::endl;
            needsCentering = false;
            this->setDirection();
        }
        if(this->getPosition().y == roomHbox.top + (160 / 2) - 24 - 1){
            this->setPosition(this->getPosition().x, this->getPosition().y + 1);
            // std::cout << "correct" << std::endl;
            needsCentering = false;
            this->setDirection();
        }
        if(this->getPosition().y == roomHbox.top + (160 / 2) - 24 + 1){
            this->setPosition(this->getPosition().x, this->getPosition().y - 1);
            // std::cout << "correct" << std::endl;
            needsCentering = false;
            this->setDirection();
        }
    }
    else{
        if((xloc == roomHbox.left + (256 / 2) - 16) && yloc == roomHbox.top + (160 / 2) - 24){
            this->possiblerooms.clear();
            // std::cout << "choose new direction now" << std::endl;
            this->setDirection();
        }
        else{
            if((this->getPosition().x == roomHbox.left + (256 / 2) - 16 - 1) || (this->getPosition().x == roomHbox.left + (256 / 2) - 16 + 1) || (this->getPosition().y == roomHbox.top + (160 / 2) - 24 - 1) || (this->getPosition().y == roomHbox.top + (160 / 2) - 24 + 1)){
                if((this->direction.x != 0) && (this->getPosition().y != roomHbox.top + (160 / 2) - 24)){
                    this->setPosition(this->getPosition().x, roomHbox.top + (160 / 2) - 24);

                    // std::cout << "yissues" << std::endl;
                    // std::cout << "corrected" << std::endl;
                }
                if((this->direction.y != 0) && (this->getPosition().x != roomHbox.left + (256 / 2) - 16)){

                    this->setPosition(roomHbox.left + (256 / 2) - 16, this->getPosition().y);
                    this->setDirection();
                    // std::cout << "xissues" << std::endl;
                    // std::cout << "corrected" << std::endl;
                }

            }
            // std::cout << xloc;
            // std::cout << " ";
            // std::cout << yloc << std::endl;
        }
    }



}
void Villain::setDirection(){
    if(g->isInsideRoom(sf::FloatRect(this->getPosition().x + 256, this->getPosition().y, hbox.width, hbox.height)) && previousString != "right"){
        // std::cout << "right" << std::endl;
        this->possiblerooms.push_back("right");
    }
    if(g->isInsideRoom(sf::FloatRect(this->getPosition().x - 256, this->getPosition().y, hbox.width, hbox.height))&& previousString != "left"){
        // std::cout << "left" << std::endl;
        this->possiblerooms.push_back("left");
    }
    if(g->isInsideRoom(sf::FloatRect(this->getPosition().x, this->getPosition().y + 160, hbox.width, hbox.height))&& previousString != "down"){
        // std::cout << "down" << std::endl;
        this->possiblerooms.push_back("down");
    }
    if(g->isInsideRoom(sf::FloatRect(this->getPosition().x, this->getPosition().y - 160, hbox.width, hbox.height))&& previousString != "up"){
        // std::cout << "up" << std::endl;
        this->possiblerooms.push_back("up");
    }
    // std::cout << this->possiblerooms.size() << std::endl;
    if(this->possiblerooms.size() == 0){
        // std::cout << this->previousString << std::endl;
        // std::cout << "no rooms found" << std::endl;
        if(this->previousString == "left"){
           this->possiblerooms.push_back("left");
        }
        else if(this->previousString == "right"){
            this->possiblerooms.push_back("right");
        }
        else if(this->previousString == "up"){
            this->possiblerooms.push_back("up");
        }
        else if(this->previousString == "down"){
            this->possiblerooms.push_back("down");
        }
    }
    this->randint = rand() % this->possiblerooms.size();
    // std::cout << "possible room random integer: ";
    // std::cout << randint << std::endl;
    // std::cout << possiblerooms.at(randint) << std::endl;
    if(this->possiblerooms.at(randint) == "right"){
        // std::cout << "moving right" << std::endl;
        this-> previousString = "left";
        this->direction.x = 1;
        this->direction.y = 0;
        curr = &walk_right;
    }
    if(this->possiblerooms.at(randint) == "left"){
        // std::cout << "moving left" << std::endl;
        this-> previousString = "right";
        this->direction.x = -1;
        this->direction.y = 0;
        curr = &walk_left;

    }
    if(this->possiblerooms.at(randint) == "up"){
        // std::cout << "moving up" << std::endl;
        this-> previousString = "down";
        this->direction.y = -1;
        this->direction.x = 0;
        curr = &walk_up;
    }
    if(this->possiblerooms.at(randint) == "down"){
        // std::cout << "moving down" << std::endl;
        this-> previousString = "up";
        this->direction.y = 1;
        this->direction.x = 0;
        curr = &walk_down;
    }

}
