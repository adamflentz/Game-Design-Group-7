#include "game/screens/GameplayScreen.hpp"
#include "engine/Random.hpp"
#include <iostream>

void GameplayScreen::init()
{
    group.generateRoomGrid(8);
    rando = std::unique_ptr<Rando>(new Rando());
    rando->setGroup(&group);
    this->addChild(std::move(rando));
}

void GameplayScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
}