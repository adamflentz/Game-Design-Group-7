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
            entity_group->getCharacter(playernumber)->onGamepadEvent(gpe);
        }
    });
    
}

void PlayerView::onUpdate(float dt)
{
    v.setCenter(entity_group->getCharacter(playernumber)->getPosition());
}

void PlayerView::setView(sf::FloatRect dimensions, sf::FloatRect viewport)
{
    v.reset(dimensions);
    v.setViewport(viewport);
}

void PlayerView::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw the rooms
    if(rooms)
        target.draw(*rooms);
    // draw the entity group
    if(entity_group)
        target.draw(*entity_group);
    // draw the current view
    target.setView(v);
}