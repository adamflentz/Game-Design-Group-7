#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <vector>
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
    void stop(){ playing = false; };
    void setLooping(bool l);
    bool isPlaying(){ return playing; };
protected:
    float time = 0;
    int curr_frame = 0;
    bool playing = true;
    sf::Sprite sprite;
    sf::Texture* texture;
    std::vector<sf::IntRect> m_frames;
private:
};

#endif