#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include "engine/GameObject.hpp"

//////////////////////////////
// GameScreen.hpp
//
// Think of GameScreens as game states and the GameEngine as a game states manager.
// 
/////////////////////////////
class GameScreen: public GameObject 
{
public:
    virtual void init(){};
    virtual bool onExit() { return true; };
    void addView(sf::View* v){ this->views.push_back(v); };
    std::string screenID;
protected:
    sf::View view;
    std::vector<sf::View*> views;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif