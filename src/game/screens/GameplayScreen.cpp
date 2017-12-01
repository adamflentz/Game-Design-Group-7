#include "game/screens/GameplayScreen.hpp"
#include "engine/Random.hpp"
#include "game/characters/Character.hpp"
#include "game/characters/Villain.hpp"
#include <iostream>

void GameplayScreen::init()
{
    group.generateRoomGrid(8);
    // If we let the playerview set its own viewport
    // then we end up running the same code over and over inside PlayerView#init
    this->createViews(numplayers);
    
}
void GameplayScreen::createViews(int numPlayers)
{
    double ratio_w = 1.0;
    double ratio_h = 1.0;
    double gutter  = 5.0; // space between player views in pixels
    double gutterx = gutter / 720.0 / 2;
    double guttery = gutter / 480.0 / 2;
    

    if(numPlayers >= 3){
        ratio_w /= 2;
        ratio_h /= 2;
    }
    else if(numPlayers == 2){
        ratio_w /= 2;
    }
    // We don't need to store these in our class definition
    // we won't use these variables after we're done here
    // so they shouldn't be members
    std::unique_ptr<PlayerView> view;
    std::shared_ptr<Character> character;
    std::shared_ptr<Villain> ghost;
    ghost = std::shared_ptr<Villain>(new Villain());
    ghost->setGroup(&group);
    ghost->setEntities(&entities);
    ghost->init();
    entities.EntityList.push_back(ghost);
    std::cout << "Finished Creating Ghost" << std::endl;
    for(int i=0; i < numPlayers; i++)
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
        character->setPlayerNumber(i);
        character->setEntities(&entities);
        this->activeCharacters.push_back(std::move(character));
        view->setCharacter(activeCharacters[i]);
        view->setCharacterList(&activeCharacters);
        view->setPlayerNumber(i);
        view->setGhost(ghost);
        this->addChild(std::move(view));
    }
    for (auto a = activeCharacters.begin(); a != activeCharacters.end(); a++){
        int count = 0;
        std::cout << (*a) << std::endl;
        std::list<std::shared_ptr<Character>> otherCharacters;
        for (auto b = activeCharacters.begin(); b != activeCharacters.end(); b++){
            if((*a) == (*b)){
                continue;
            }
            else{
                otherCharacters.push_back((*b));
            }
        }
        (*a)->setCharacterList(&otherCharacters);
        (*a)->init();
    }
}   

  
void GameplayScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
}
