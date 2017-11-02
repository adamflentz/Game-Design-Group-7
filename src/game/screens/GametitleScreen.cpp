#include "game/screens/GametitleScreen.hpp"
#include <iostream>

void GametitleScreen::init()
{
  std::cout<< "TitleScreen" << std::endl;
  // Instead of doing this:
  //    this->engine->changeGameScreen("GamePlay");
  // We can use the events system. The advantage is that
  // this will work from anywhere in our program and we don't
  // need to have a reference to our engine. 

  // create an event as a shared pointer with data type string
  auto event = std::make_shared< Event<std::string> >("GamePlay"); 
  Events::postEvent("change_screen", event);           // Post the event
}

void GametitleScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
}
