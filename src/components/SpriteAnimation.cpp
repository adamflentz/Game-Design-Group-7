#include "components/SpriteAnimation.hpp"
#include <iostream>

void SpriteAnimation::setSpriteSheet(sf::Texture& t)
{
    texture = &t; 
    sprite.setTexture(t);  }

void SpriteAnimation::addFrames(std::vector< std::vector<int> > frames, int tilew, int tileh)
{
    for(auto a = frames.begin(); a != frames.end(); a++ ){
        this->addFrame(*a, tilew, tileh);
    }
}

void SpriteAnimation::addFrame(std::vector<int> frame, int tilew, int tileh)
{
    // get the size of the texture
    sf::Vector2u size = (*(this->texture)).getSize();
    int tilesPerRow = size.x / tilew; 
    // TODO: Factor in sprite width and sprite height in order to account
    //       for larger sprite compositions
    for(auto a = frame.begin(); a != frame.end(); a++){
        int tilenum = *a;
        int tx = tilenum % tilesPerRow;
        int ty = tilenum / tilesPerRow;
        this->m_frames.push_back(sf::IntRect(tx*tilew, ty*tileh, tilew, tileh));
        // set the first frame
        if(m_frames.size() == 1)
            sprite.setTextureRect(m_frames.at(0));

    }
}

void SpriteAnimation::nextFrame(float dt)
{
    if(!this->playing)
        return;
    this->time += dt;
    if(this->time < 6.0 * dt)
        return;
    // update the sprite rect
    sprite.setTextureRect(m_frames.at(curr_frame));
    // go to the next frame
    curr_frame = (curr_frame + 1) % m_frames.size();
    this->time = 0;
}

void SpriteAnimation::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw sprite
    target.draw(sprite, states);
}