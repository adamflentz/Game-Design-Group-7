#include "game/screens/GameplayScreen.hpp"
#include "engine/Random.hpp"
#include "game/characters/Character.hpp"
#include "game/characters/Villain.hpp"
#include <iostream>

void GameplayScreen::init()
{
    group.generateRoomGrid(20);
    ghost = std::shared_ptr<Villain>(new Villain());
    ghost->setGroup(&group);
    ghost->init();
    for(int i=0; i < numplayers; i++)
    {
        view = std::unique_ptr<PlayerView>(new PlayerView());
        view->setRoomGroup(&group);
        character = std::shared_ptr<Character>(new Character());
        character->setGroup(&group);
        character->init();
        this->activeCharacters.push_back(std::move(character));
        view->setGhost(ghost);
        view->setTotalPlayers(numplayers);
        view->setPlayerNumber(i);
        view->setCharacter(activeCharacters[i]);
        view->setCharacterList(&activeCharacters);
        this->addChild(std::move(view));
    }
    
}
void GameplayScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
}
