#include "game/screens/CharacterScreen.hpp"
#include <iostream>

void CharacterScreen::init()
{
  std::cout<< "CharacterScreen" << std::endl;

  Events::addEventListener("gamepad_event", [=](base_event_type e){
      // We'll need to delete this listener in the destructor or we'll have segfaults/undefined behavior eventually
      // Cast to gamepad event
      auto gpe = dynamic_cast< GamepadEvent& >(*e);
      // Check that the index matches our player
      this->onGamepadEvent(gpe);

      // if(gpe.index == playernumber){
      //     // Call our listener function personally
      //     c->onGamepadEvent(gpe);
      // }
  });

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
  // title screen emerges from darkness

  if (trans > 50) {
    trans -= dt/60;
    blackness.setFillColor(sf::Color(0, 0, 0, trans));
  }
};

void CharacterScreen::onGamepadEvent(GamepadEvent e){
  if(e.type == GamepadEvent::RELEASED)
    return;
  if(this->changed)
    return;
  auto event = std::make_shared< Event<std::string> >("GamePlay");
  this->changed = true;
  Events::triggerEvent("change_screen", event);
}

void CharacterScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
    ctx.draw(sprite);
    ctx.draw(blackness);
}
