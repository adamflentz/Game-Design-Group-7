#include "game/screens/GameplayScreen.hpp"

void GameplayScreen::init()
{
    rando = std::unique_ptr<Rando>(new Rando());
    this->addChild(std::move(rando));
}