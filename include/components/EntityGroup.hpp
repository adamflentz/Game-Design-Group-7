#ifndef ENTITYGROUP_HPP
#define ENTITYGROUP_HPP

#include "engine/Engine.hpp"
#include <memory>
#include <iostream>
#include <set>
#include <vector>
// #include <sort>

/**
* Currently this class is not used, but here's an idea
* that would require minor refactoring of the codebase.
* This class could contain separate lists of 'entities'
* in the game that are required to be interactable. 
*/

class Character; // forward declearation
class Clue;
/**
* A group that contains items that can interact with each other
*/
class EntityGroup: public GameObject
{
public:
    void init();
    void addCharacter(std::shared_ptr<Character> c);
    void addClue(std::shared_ptr<Clue> clue);
    std::vector<std::shared_ptr<Character>> getCharacters();
    std::vector<std::shared_ptr<Clue>> getClues();
    std::shared_ptr<Character> getCharacter(int pnum);
    std::shared_ptr<Clue> getClue(int cnum);
    void onUpdate(float dt);
    void drawInArea(sf::RenderTarget& ctx, sf::FloatRect box) const;
protected:
    std::vector<std::shared_ptr<Character>> characters;
    std::vector<std::shared_ptr<Clue>> clues;
    // Draw all the entities
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
};

#include "game/characters/Character.hpp"
#include "game/objects/Clue.hpp"

#endif
