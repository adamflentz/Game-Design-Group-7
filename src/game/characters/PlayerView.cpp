#include <vector>
#include <iostream>
#include "game/characters/PlayerView.hpp"

void PlayerView::init()
{
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
    // center the view around the character
    // TODO: This is actually the top-left corner of the character
    v.setCenter(c->getPosition());
    // zoom out a little
    v.zoom(0.5f);    
}

void PlayerView::setView(sf::FloatRect dimensions, sf::FloatRect viewport){
    v.reset(dimensions);
    v.setViewport(viewport);
}

void PlayerView::onUpdate(float dt)
{
    c->onUpdate(dt);
    v.setCenter(c->getPosition());
}

void PlayerView::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*rooms);
    // draw each individual character
    for(auto it = charVector->begin(); it != charVector->end(); it++)
    {
        target.draw(**it);
    }
    // draw the current view
    target.setView(v);


}