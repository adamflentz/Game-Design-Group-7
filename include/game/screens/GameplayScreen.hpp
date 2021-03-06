#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "engine/Engine.hpp"
#include "game/characters/Character.hpp"
#include "game/characters/Villain.hpp"
#include "game/objects/Clue.hpp"
#include "game/rooms/RoomGroup.hpp"
#include "game/characters/PlayerView.hpp"
#include "components/EntityGroup.hpp"

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
    void onUpdate(float dt);
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;

protected:
    void createViews(int numPlayers);
    void createClues();
    int phase = 1;
    int num_players = 1;
    int hiLow;
    // Entity 0 is the ghost
    std::map<int, std::shared_ptr <Clue>> clues;
    // A map of entities (characters)
    // Entity 0 is the ghost
    std::map<int, std::shared_ptr<Character>> entities;

    sf::Clock clock;
    RoomGroup group;
    std::vector< std::unique_ptr<PlayerView> > views;
    std::shared_ptr<Villain> ghost;
    std::shared_ptr<Clue> clue;
    EntityGroup entity_group;
    ClueReader reader;
    sf::Sound hunt;
};
