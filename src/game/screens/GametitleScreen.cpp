#include "game/screens/GametitleScreen.hpp"
#include "engine/Random.hpp"
#include <iostream>

void GametitleScreen::init()
{
  std::cout<< "TitleScreen" << std::endl;
  // this->engine->changeGameScreen("GamePlay");
}

void GametitleScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
}
