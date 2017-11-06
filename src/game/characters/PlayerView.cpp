#include <vector>
#include <iostream>
#include "game/characters/PlayerView.hpp"

void PlayerView::init()
{
    switch(totalplayernumber){
        case 1: v.reset(sf::FloatRect(0,0,720,480));
        v.setCenter(c->getPosition());
        v.zoom(0.5f);
        break;
        case 2:switch(playernumber){
            case 0:v.setViewport(sf::FloatRect(0,0,0.5f,1.0f));
            v.setSize(720/2, 360);
            v.setCenter(c->getPosition());
            v.zoom(0.5f);
            break;
            case 1:v.setViewport(sf::FloatRect(0.5f,0,0.5f,1.0f));
            v.setSize(720/2, 360);
            v.setCenter(c->getPosition());
            v.zoom(0.5f);
            break;
    
        break;
        }

    }
    
}

void PlayerView::onUpdate(float dt)
{
    c->onUpdate(dt);
    v.setCenter(c->getPosition());
}

void PlayerView::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw each individual character
    for(auto it = charVector->begin(); it != charVector->end(); it++)
    {
        target.draw(**it);
    }
    // draw the current view
    target.setView(v);


}