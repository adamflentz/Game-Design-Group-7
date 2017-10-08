#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"

class SpriteAnimation: public sf::Drawable, public sf::Transformable
{
public:
    SpriteAnimation(){};
    void setSpriteSheet(sf::Texture& t);
    void addFrames(std::vector< std::vector<int> > frames, int tilew, int tileh);
    void addFrame(std::vector<int> frame, int tilew, int tileh);
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
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif