#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include "engine/GameObject.hpp"

class GameEngine;

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
    void setEngine(GameEngine* e) { this->engine = e; };
    std::string screenID;
protected:
  GameEngine* engine;
};

#include "engine/GameEngine.hpp"

#endif
