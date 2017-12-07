#include <vector>
#include <iostream>
#include "game/characters/PlayerView.hpp"

void PlayerView::init()
{
    itemBar.setSize(sf::Vector2f(20, 20));
    itemBar.setOutlineColor(sf::Color::White);
    itemBar.setFillColor(sf::Color::Transparent);
    itemBar.setOutlineThickness(2);
    //pain.setFillColor(sf::Color::Red);
    painCount = 100;
    pain.setFillColor(sf::Color(255, 0, 0, painCount));

    heartTexture = *ResourceManager::getTexture("../resources/sprites/heart.png");

    // setup event listeners (lazy method)
    Events::addEventListener("gamepad_event", [=](base_event_type e){
        // We'll need to delete this listener in the destructor or we'll have segfaults/undefined behavior eventually
        // Cast to gamepad event
        auto gpe = dynamic_cast< GamepadEvent& >(*e);
        // Check that the index matches our player
        if(gpe.index == entity_group->getCharacter(playernumber)->getGamepadIndex()){
            // Call our listener function personally
            entity_group->getCharacter(playernumber)->onGamepadEvent(gpe);
        }
    });

}

void PlayerView::onUpdate(float dt)
{
    v.setCenter(entity_group->getCharacter(playernumber)->getPosition());
    bool invul = entity_group->getCharacter(playernumber)->invul;
    if(invul && painCount > 0){
        pain.setFillColor(sf::Color(255, 0, 0, painCount));
        painCount--;
    }
    else if(!invul)
       painCount = 100;
}

void PlayerView::setView(sf::FloatRect dimensions, sf::FloatRect viewport)
{
    viewDimensions = dimensions;
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

    //
    if(rooms){
        Room* room = rooms->getRoomInside(entity_group->getCharacter(playernumber)->hbox);
        // Now this just draws the doors lol
        if(NULL != room){
            target.draw(*room);
            target.draw(*rooms);
            // draw the entities in the current room
            if(entity_group){
                entity_group->drawInArea(target, room->hbox);
            }
        }
    }
    // draw the HUD
    target.setView(HUD);
    // target.draw(itemBar);
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

    // draw a clue
    if(entity_group->getCharacter(playernumber)->readClue == true && entity_group->getCharacter(playernumber)->atClue == true){
        // background box
        sf::RectangleShape bgBox;
        sf::Vector2f v(viewDimensions.width - 40, 40);
        bgBox.setSize(v);
        bgBox.setFillColor(sf::Color::Black);
        bgBox.setPosition(20, viewDimensions.height - 60);

        // text
        std::string t;
        if(entity_group->getCharacter(playernumber)->currentClue != NULL){
            t = entity_group->getCharacter(playernumber)->currentClue->setClue;
        }

        sf::Text clueText;
        clueText.setFont(*ResourceManager::getFont("../resources/fonts/Underdog-Regular.ttf"));
        if(t != ""){
            clueText.setString(t);
        }
        clueText.setCharacterSize(24);
        clueText.setColor(sf::Color::White);
        clueText.setStyle(sf::Text::Bold);
        clueText.setPosition(30, viewDimensions.height - 55);

        target.draw(bgBox);
        target.draw(clueText);
    }
}
