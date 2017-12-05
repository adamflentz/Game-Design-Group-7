#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include "game/Config.hpp"
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
    void setConfig(std::shared_ptr<Config> c){config = c;};
    std::string screenID;
protected:
    std::shared_ptr<Config> config;
    GameEngine* engine;
};

#include "engine/GameEngine.hpp"

#endif
