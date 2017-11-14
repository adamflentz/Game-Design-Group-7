#include "game/screens/CharacterScreen.hpp"
#include <iostream>

void CharacterScreen::init()
{
  std::cout<< "CharacterScreen" << std::endl;

  if (!title.loadFromFile("../resources/character.png"))
  {
      return;
  }

  sprite.setTexture(title);

  blackness.setSize(sf::Vector2f(720, 480));

  blackness.setFillColor(sf::Color(0, 0, 0, trans));

  // this->engine->changeGameScreen("GamePlay");

  // Instead of doing this:
  //    this->engine->changeGameScreen("GamePlay");
  // We can use the events system. The advantage is that
  // this will work from anywhere in our program and we don't
  // need to have a reference to our engine.

  // create an event as a shared pointer with data type string
  // auto event = std::make_shared< Event<std::string> >("GamePlay");
  // add the event to the queue
  // Events::queueEvent("change_screen", event);

}

void CharacterScreen::onUpdate(float dt){
  // if alpha != 0
  // variable = clock.reset()
  // if(variable > some amount)
  // subtract from alpha/transparency
  // trans *= dt / 1200;
  // blackness.setFillColor(sf::Color(0, 0, 0, trans));

  if (trans > 50) {
    trans -= dt/60;
    blackness.setFillColor(sf::Color(0, 0, 0, trans));
  }
};

void CharacterScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
    ctx.draw(sprite);
    ctx.draw(blackness);
}
