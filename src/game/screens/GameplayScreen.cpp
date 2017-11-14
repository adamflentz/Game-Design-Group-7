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
        // Map i to a 2d array [2][2]
        int x = i % 2;
        int y = i / 2;
        view = std::unique_ptr<PlayerView>(new PlayerView());
        view->setRoomGroup(&group);
        // Define player view (using math)
        view->setView(
            sf::FloatRect(0, 0, 720 * ratio_w, 480 * ratio_h), 
            sf::FloatRect((ratio_w + gutterx) * x, (ratio_h  + guttery) * y, ratio_w - gutterx * (1.0 - x), ratio_h - guttery * (1.0 - y))
        );

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
