#include <memory>
#include "engine/Engine.hpp"
#include "game/characters/rando.hpp"

//////////////////////////
// PlayScreen.hpp
//
// This is the screen in which users will go to when the game starts.
// A logical progression for screens might be something like:
//
// Start_Screen -> Character_Select_Screen -> Gameplay_screen (this)-.
// ^               ^                          ^                      |
// |               |                          |                      |
// ---------------------------------------------Game_Over_Screen <---
//
// There could even potentially be loading screens.
// 
// This screen is pretty simple. All it does is show a character.
//
// Next check out src/GameplayScreen.cpp
//////////////////////////

class GameplayScreen: public GameScreen
{
public:
    void init();
protected:
    std::unique_ptr<GameObject> rando;
};