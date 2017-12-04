#include <vector>
#include <iostream>
#include "game/characters/PlayerView.hpp"

void PlayerView::init()
{
    itemBar.setSize(sf::Vector2f(20, 20));
    itemBar.setOutlineColor(sf::Color::White);
    itemBar.setFillColor(sf::Color::Transparent);
    itemBar.setOutlineThickness(2);
    pain.setFillColor(sf::Color::Red);
    pain.setFillColor(sf::Color(255, 0, 0, 180));
    painCount = 180;

    if (!heartTexture.loadFromFile("../resources/sprites/heart.png")) {
      return;
    }

    // setup event listeners (lazy method)
    Events::addEventListener("gamepad_event", [=](base_event_type e){
        // We'll need to delete this listener in the destructor or we'll have segfaults/undefined behavior eventually
        // Cast to gamepad event
        auto gpe = dynamic_cast< GamepadEvent& >(*e);
        // Check that the index matches our player
        if(gpe.index == playernumber){
            // Call our listener function personally
            entity_group->getCharacter(playernumber)->onGamepadEvent(gpe);
        }
    });

}

void PlayerView::onUpdate(float dt)
{
    v.setCenter(entity_group->getCharacter(playernumber)->getPosition());
    if(entity_group->getCharacter(playernumber)->invul == true){
        pain.setFillColor(sf::Color(255, 0, 0, painCount));
        painCount--;
    }
}

void PlayerView::setView(sf::FloatRect dimensions, sf::FloatRect viewport)
{
    v.reset(dimensions);
    v.setViewport(viewport);
    HUD.reset(dimensions);
    HUD.setViewport(viewport);
    itemBar.setPosition(viewport.left + dimensions.width - 40, viewport.top + dimensions.height - 40);
    pain.setSize(sf::Vector2f(dimensions.width, dimensions.height));
}

void PlayerView::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw the current view
    target.setView(v);

    if(rooms)
        target.draw(*rooms);
    // draw the entity group
    if(entity_group)
        target.draw(*entity_group);
    // draw the HUD
    target.setView(HUD);
    target.draw(itemBar);
    if(entity_group->getCharacter(playernumber)->invul == true){
        // pain.setFillColor(sf::Color(255, 0, 0, painCount));
        // painCount--;
        target.draw(pain);
    }
    // std::cout << entity_group->getCharacter(playernumber)->maxHealth << std::endl;
    for(int i = 0; i < entity_group->getCharacter(playernumber)->maxHealth; i++){
        sf::Sprite heart;
        heart.setTexture(heartTexture);
        if(entity_group->getCharacter(playernumber)->health > i){
            heart.setTextureRect(sf::IntRect(0, 0, 300, 300));
        }
        else{
            heart.setTextureRect(sf::IntRect(600, 0, 300, 300));
        }
        heart.scale(sf::Vector2f(0.1, 0.1));
        heart.setPosition(i * 30, 0);
        target.draw(heart);
    }
}