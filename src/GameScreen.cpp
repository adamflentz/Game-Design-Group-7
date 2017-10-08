#include "engine/GameScreen.hpp"

// Initiates the render for all children
void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    this->onDraw(target);
    // TODO: if no view, push global view
    /*for(auto v = this->views.begin(); v!= this->views.end(); v++){
        target.setView(**v);/**/
        for(auto a = this->children.begin(); a != this->children.end(); a++){
            target.draw(**a, states);
        }
    /*}*/
}/**/