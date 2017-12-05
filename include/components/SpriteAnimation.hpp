/////////////////
// SpriteAnimation.hpp
//
// Create an animated sprite
//
////////////////


#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"

class SpriteAnimation: public GameObject
{
public:
    SpriteAnimation(){};
    void setSpriteSheet(sf::Texture& t);
    void addFrames(std::vector< std::vector<int> > frames, int tilew, int tileh);
    void addFrame(std::vector<int> frame, int tilew, int tileh);
    //void onUpdate(float dt){ sprite.setPosition(this->getPosition()); };
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    // controls
    void nextFrame(float dt);
    void gotoFrame();
    void play(){ playing = true; };
    void play(std::function<void()> cb){
        playing = true;
        onComplete = cb; 
        performAfterPlayer = true;
    };
    void stop(){ playing = false; };
    void setLooping(bool l);
    bool isPlaying(){ return playing; };
protected:
    std::function<void()> onComplete;
    float time = 0;
    int curr_frame = 0;
    bool playing = true;
    bool performAfterPlayer = false;
    sf::Sprite sprite;
    sf::Texture* texture;
    std::vector<sf::IntRect> m_frames;
private:
};

#endif