#include <SFML/Graphics.hpp>
#include <memory>
#include "engine/Engine.hpp"
#include "game/characters/Character.hpp"
#include "game/rooms/RoomGroup.hpp"
#include "game/characters/PlayerView.hpp"

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
    int numplayers = 2;
    std::unique_ptr<PlayerView> view;
    std::vector<std::shared_ptr<Character>> activeCharacters;
    std::shared_ptr<Character> character;
    // std::vector<std::unique_ptr<Room> > roomFac;
    RoomGroup group;
};