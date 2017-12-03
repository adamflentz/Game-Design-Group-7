#include <memory>
#include <map>
#include "engine/Engine.hpp"
#include "game/screens/GameplayScreen.hpp"
#include "game/screens/GametitleScreen.hpp"
#include "game/screens/CharacterScreen.hpp"

////////////////////////
// HouseHaunters.hpp
//
// This is the HouseHaunters game engine.
// The Game engine's primary jobs include handling the creation and deletion
// of the window, managing the switching of game screens, and starting and
// stopping the main game loop. All of this is handled by the GameEngine class
// so all we need to do is initialize our game by adding screens.
//
// Next check out src/HouseHaunters.cpp
///////////////////////

class HouseHauntersGame: public GameEngine
{
private:
    // This is an overridden virtual method that gets called
    // automatically when the game starts.
    void init();
protected:
    std::shared_ptr<Config> config;
};
