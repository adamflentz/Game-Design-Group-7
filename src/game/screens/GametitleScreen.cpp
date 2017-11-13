#include "game/screens/GametitleScreen.hpp"
#include "engine/Random.hpp"
#include <iostream>

void GametitleScreen::init()
{
  std::cout<< "TitleScreen" << std::endl;

  if (!title.loadFromFile("../resources/titlescreen.png"))
  {
      return;
  }

  sprite.setTexture(title);
  // this->engine->changeGameScreen("GamePlay");
}

void GametitleScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
    ctx.draw(sprite);
}
