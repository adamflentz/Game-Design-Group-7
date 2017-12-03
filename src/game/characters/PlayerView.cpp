#include <vector>
#include <iostream>
#include "game/characters/PlayerView.hpp"

void PlayerView::init()
{
    itemBar.setSize(sf::Vector2f(20, 20));
    itemBar.setOutlineColor(sf::Color::White);
    itemBar.setFillColor(sf::Color(150, 50, 250));
    itemBar.setOutlineThickness(2);
    // setup event listeners (lazy method)
    Events::addEventListener("gamepad_event", [=](base_event_type e){
        // We'll need to delete this listener in the destructor or we'll have segfaults/undefined behavior eventually
        // Cast to gamepad event
        auto gpe = dynamic_cast< GamepadEvent& >(*e);
        // Check that the index matches our player
        if(gpe.index == playernumber){
            // Call our listener function personally
            c->onGamepadEvent(gpe);
        }
    });

}

void PlayerView::onUpdate(float dt)
{
    c->onUpdate(dt);
    g->onUpdate(dt);
    v.setCenter(c->getPosition());

}

void PlayerView::setView(sf::FloatRect dimensions, sf::FloatRect viewport){
    v.reset(dimensions);
    v.setViewport(viewport);
    HUD.reset(dimensions);
    HUD.setViewport(viewport);
    itemBar.setPosition(viewport.left + dimensions.width - 40, viewport.top + dimensions.height - 40);
}

void PlayerView::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // draw the current view
    target.setView(v);
    target.draw(*rooms);
    // draw each individual character
    for(auto it = charVector->begin(); it != charVector->end(); it++)
    {
        target.draw(**it);
    }
    target.draw(*g);

    target.setView(HUD);
    target.draw(itemBar);
}
