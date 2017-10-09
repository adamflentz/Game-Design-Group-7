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
    std::string screenID;
protected:
};

#endif