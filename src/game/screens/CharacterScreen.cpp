#include "game/screens/CharacterScreen.hpp"
#include <iostream>
void CharacterIcon::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
  // std::cout << t.getPosition().y << std::endl;
  ctx.draw(t, states);
}

std::vector<std::unique_ptr<CharacterIcon>>::iterator CharacterSelection::find(int player){
  return std::find_if(hovering.begin(), hovering.end(), [=](std::unique_ptr<CharacterIcon>& c){ 
    return c->getPlayer() == player; 
    }
  );
}

void CharacterSelection::setPortraitTexture(std::string texture)
{
  portrait.setTexture(*ResourceManager::getTexture(texture));
}

void CharacterSelection::removePlayer(int player)
{
  auto it = find(player);
  if(it != hovering.end())
    hovering.erase(it);

}

void CharacterSelection::addPlayer(int player)
{
  auto it = find(player);
  if(it == hovering.end()){
    std::unique_ptr<CharacterIcon> c = std::unique_ptr<CharacterIcon>(new CharacterIcon());
    c->setPlayer(player);
    c->setFont("../resources/fonts/Underdog-Regular.ttf");
    c->setColor(colors[(player-1)%4]);
    hovering.push_back(std::move(c));
  }
}

bool CharacterSelection::hasPlayer(int player)
{
  auto it = find(player);
  if(it != hovering.end())
    return true;
}

void CharacterSelection::onUpdate(float dt)
{
  float width = 150; // For now this is some arbitrary number
  float elements = hovering.size();
  float box_size = 30;
  float padding = 5;
  float xpos = (width / 2 ) - ( (elements * box_size) + (elements -1) * padding ) / 2;
  for(auto it = hovering.begin(); it != hovering.end(); it++){
    (*it)->setPosition(xpos, 265.0f);
    // std::cout << (*it)->getPosition().x << std::endl;
    xpos += 35;
  }
}

void CharacterSelection::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
  for(auto it = hovering.begin(); it != hovering.end(); it++){
    ctx.draw(**it, states);
  }
  ctx.draw(portrait, states);
}



void CharacterScreen::init()
{
  std::cout<< "CharacterScreen" << std::endl;

  player_num = config->player_map.size();

  // Initialize the character portraits
  float xpos = 40;
  for(int i = 0; i < 4; i++){
    std::unique_ptr<CharacterSelection> c = std::unique_ptr<CharacterSelection>(new CharacterSelection());
    c->setPortraitTexture("../resources/sprites/white_chara.png");
    c->setPosition(xpos, 120.0f);
    this->char_selections.push_back(std::move(c));
    xpos += (720.0 - 4.0f*15.0f) / 4.0f ;
  }

  // Initialize player 1
  this->addPlayer(player_num, config->player_map.begin()->second);

  // listen for gamepad events
  Events::addEventListener("gamepad_event", [=](base_event_type e){
      auto gpe = dynamic_cast< GamepadEvent& >(*e);
      this->onGamepadEvent(gpe);
  });

  background.setSize(sf::Vector2f(720, 480));
  background.setFillColor(sf::Color(30, 30, 30));

  teamFont.setFont(*ResourceManager::getFont("../resources/fonts/Underdog-Regular.ttf"));
  teamFont.setString("MAKE YOUR TEAM");
  teamFont.setCharacterSize(24);
  //teamFont.setColor(sf::Color::White);
  teamFont.setStyle(sf::Text::Bold);
  teamFont.setPosition(250, 50);


  blackness.setSize(sf::Vector2f(720, 480));
  blackness.setFillColor(sf::Color(0, 0, 0, trans));
}

void CharacterScreen::onUpdate(float dt)
{
  // title screen emerges from darkness
  if (trans > 50) {
    trans -= dt/60;
    blackness.setFillColor(sf::Color(0, 0, 0, trans));
  }
  // Set the positions of the texts
  for(auto it = char_selections.begin(); it != char_selections.end(); it++){
    (*it)->update(dt);
  }
};

void CharacterScreen::addPlayer(int index, int num)
{
  config->player_map[index] = num;
  // get first available character and set position
  for(auto it = char_selections.begin(); it != char_selections.end(); it++){
    if(!((*it)->isSelected()) && (*it)->isEmpty()){
      (*it)->addPlayer(num);
      return;
    }
  }
}

void CharacterScreen::onGamepadEvent(GamepadEvent e)
{
  if(this->changed)
    return;
  
  // std::cout << e.index << std::endl;
  if(e.type == GamepadEvent::RELEASED){
    // Check if player in game already (add them if possible)
    if(player_num < 4 && config->player_map.count(e.index) == 0){
      player_num++;
      this->addPlayer(e.index, player_num);
    }
    // Handle input 
    else {
      int player = config->player_map[e.index];
      int found_index = -1;
      int replace_index = -1;
      bool found = false;
      
      if(e.button == "RIGHT"){
        int index = 0;
        for(auto it = char_selections.begin(); it != char_selections.end(); it++){
          if(!found && (*it)->hasPlayer(player)){
            if((*it)->isSelected() && (*it)->getPlayer() == player)
              break;
            found_index = index;
            found = true;
          }else if(found){
            replace_index = index;
            break;
          }
          index++;
        }
      }
      else if(e.button == "LEFT"){
        int index = char_selections.size() - 1;
        for(auto it = char_selections.rbegin(); it != char_selections.rend(); it++){
          if(!found && (*it)->hasPlayer(player)){
            if((*it)->isSelected() && (*it)->getPlayer() == player)
              break;
            found_index = index;
            found = true;
          }else if(found){
            replace_index = index;
            break;
          }
          index--;
        }
      }
      
      else if(e.button == "A"){
        for(auto it = char_selections.begin(); it != char_selections.end(); it++){
          if((*it)->isSelected())
            continue;
          if((*it)->hasPlayer(player)){
            (*it)->setPlayer(player);
            selected_count++;
            break;
          }
        }
        if(selected_count == player_num){
          // Everybody selected a character. Let's set that in the config then move on
          std::cout << "Everybody's selected something" << std::endl;
          auto event = std::make_shared< Event<std::string> >("GamePlay");
          this->changed = true;
          // Set the configurations
          config->num_players = selected_count;


          Events::queueEvent("change_screen", event);
          return;
        }
      }
      else if(e.button == "B"){
        for(auto it = char_selections.begin(); it != char_selections.end(); it++){
          if((*it)->isSelected()){
            if((*it)->hasPlayer(player)){
              (*it)->unsetPlayer();
              selected_count--;
              break;
            }
          }
        }
      }
      // Move the character if neccessary 
      if(found_index >= 0 && found_index < 4 && replace_index >= 0 && replace_index < 4){
          // std::cout << "Moving player " << player << " from index " << found_index << " to index " << replace_index << std::endl; 
          char_selections[found_index]->removePlayer(player);
          char_selections[replace_index]->addPlayer(player);
      }
    }
  }
}

void CharacterScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    // ctx.draw(group, states);
    ctx.draw(background);
    ctx.draw(teamFont);
    
    for(auto it = char_selections.begin(); it != char_selections.end(); it++){
      ctx.draw(**it);
    }

    // for(auto it = texts.begin(); it != texts.end(); it++){
    //   ctx.draw(**it);
    // }
    // std::cout << "oh shit" << std::endl;
    ctx.draw(blackness);
}
