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


  if (!chara1_pic.loadFromFile("../resources/white_chara.png"))
  {
      return;
  }

  if (!font.loadFromFile("../resources/Underdog-Regular.ttf"))
  {
      return;
  }

  background.setSize(sf::Vector2f(720, 480));
  background.setFillColor(sf::Color(30, 30, 30));

  teamFont.setFont(font);
  teamFont.setString("MAKE YOUR TEAM");
  teamFont.setCharacterSize(24);
  //teamFont.setColor(sf::Color::White);
  teamFont.setStyle(sf::Text::Bold);
  teamFont.setPosition(250, 50);

  chara1.setPosition(sf::Vector2f(49, 90));
  chara1.setTexture(chara1_pic);

  chara2.setPosition(sf::Vector2f(207, 90));
  chara2.setTexture(chara1_pic);

  chara3.setPosition(sf::Vector2f(365, 90));
  chara3.setTexture(chara1_pic);

  chara4.setPosition(sf::Vector2f(523, 90));
  chara4.setTexture(chara1_pic);

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
  std::map<int, int> player_map;
  // if player not in map
  // increment number of players
  // add player to the map with player number

  // if player in map
  // use the button event to change player's selected charaacter

  // auto event = std::make_shared< Event<std::string> >("GamePlay");
  // this->changed = true;
  // Events::triggerEvent("change_screen", event);
}

void CharacterScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
    ctx.draw(background);
    ctx.draw(teamFont);
    ctx.draw(chara1);
    ctx.draw(chara2);
    ctx.draw(chara3);
    ctx.draw(chara4);
    ctx.draw(blackness);
}
