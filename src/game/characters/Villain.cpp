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
    this->previousLocationX = this->getPosition().x;
    this->previousLocationY = this->getPosition().y;
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
}

void Villain::onUpdate(float dt)
{   
    int dx = this->direction.x * speed * dt;
    int dy = this->direction.y * speed * dt;
    // check if inside room 
    this->wander();
    // Set z index
    this->z_index = this->getPosition().y + 20;

    // check for collisions
    this->checkCollisions();
    if(g->isInsideRoom(sf::FloatRect(hbox.left + dx, hbox.top + dy, hbox.width, hbox.height))){
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

void Villain::wander()
{
    
    int xloc = this->getPosition().x;
    int yloc = this->getPosition().y;
    // std::cout << "x: ";
    // std::cout << this->previousLocationX;
    // std::cout << " ";
    // std::cout << xloc << std:: endl;
    // std::cout << "y: ";
    // std::cout << this->previousLocationY;
    // std::cout << " ";
    // std::cout << yloc << std:: endl;
    if(this->previousLocationX + 266 == xloc  && this->getPosition().y == this->previousLocationY){
        // std::cout << "switch" << std::endl;
        this->previousLocationX = xloc + 1;
        this->previousLocationY = yloc;
        this->roomCenterX = xloc + 1;
        this->roomCenterY = yloc;
        this->possiblerooms.clear();
        this->direction.x = 0;
        this->setDirection();
        // std::cout << "x: ";
        // std::cout << this->previousLocationX;
        // std::cout << " ";
        // std::cout << xloc << std:: endl;
        // std::cout << "y: ";
        // std::cout << this->previousLocationY;
        // std::cout << " ";
        // std::cout << yloc << std:: endl;

    }
    else if(this->previousLocationX - 266 == xloc  && this->getPosition().y == this->previousLocationY){
        // std::cout << "switch" << std::endl;
        this->previousLocationX = xloc - 1;
        this->previousLocationY = yloc;
        this->roomCenterX = xloc - 1;
        this->roomCenterY = yloc;
        this->possiblerooms.clear();
        this->direction.x = 0;
        this->setDirection();
        // std::cout << "x: ";
        // std::cout << this->previousLocationX;
        // std::cout << " ";
        // std::cout << xloc << std:: endl;
        // std::cout << "y: ";
        // std::cout << this->previousLocationY;
        // std::cout << " ";
        // std::cout << yloc << std:: endl;
    }
    else if(this->previousLocationY + 170 == yloc && this->getPosition().x == this->previousLocationX){
        // std::cout << "switch" << std::endl;
        this->previousLocationX = xloc;
        this->previousLocationY = yloc + 1;  
        this->roomCenterX = xloc;
        this->roomCenterY = yloc + 1;
        this->possiblerooms.clear();
        this->direction.y = 0;
        this->setDirection();  
        // std::cout << "x: ";
        // std::cout << this->previousLocationX;
        // std::cout << " ";
        // std::cout << xloc << std:: endl;
        // std::cout << "y: ";
        // std::cout << this->previousLocationY;
        // std::cout << " ";
        // std::cout << yloc << std:: endl;
    }   
    else if(this->previousLocationY - 170 == yloc && this->getPosition().x == this->previousLocationX){
        // std::cout << "switch" << std::endl;
        this->previousLocationX = xloc;
        this->previousLocationY = yloc - 1;
        this->roomCenterX = xloc;
        this->roomCenterY = yloc - 1;
        this->possiblerooms.clear();
        this->direction.y = 0;
        this->setDirection();   
        // std::cout << "x: ";
        // std::cout << this->previousLocationX;
        // std::cout << " ";
        // std::cout << xloc << std:: endl;
        // std::cout << "y: ";
        // std::cout << this->previousLocationY;
        // std::cout << " ";
        // std::cout << yloc << std:: endl;
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