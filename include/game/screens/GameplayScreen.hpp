#include <SFML/Graphics.hpp>
#include <memory>
#include "engine/Engine.hpp"
#include "game/characters/rando.hpp"
#include "game/rooms/RoomGroup.hpp"

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
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
protected:
    std::unique_ptr<Rando> rando;
    // std::vector<std::unique_ptr<Room> > roomFac;
    RoomGroup group;
};