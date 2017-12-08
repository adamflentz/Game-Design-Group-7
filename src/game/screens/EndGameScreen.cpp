#include "game/screens/EndGameScreen.hpp"
#include <iostream>

void EndGameScreen::init() {
    text.setString("Game Over");
    text.setFont(*ResourceManager::getFont("../resources/fonts/youmurderer.ttf"));
    text.setCharacterSize(100);
    sf::FloatRect pos = text.getLocalBounds();
    text.setPosition(720/2, 480/2);
    text.setOrigin(pos.left + pos.width / 2, pos.top + pos.height / 2);
    over.setBuffer(*ResourceManager::getSoundBuffer("../resources/music/gameover.flac"));
    over.play();
    blackness.setSize(sf::Vector2f(720, 480));
    blackness.setFillColor(sf::Color(0, 0, 0, trans));
}

void EndGameScreen::onUpdate(float dt){

  if (trans > 50) {
    trans -= dt/60;
    blackness.setFillColor(sf::Color(0, 0, 0, trans));
  }
};


void EndGameScreen::onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
{
    ctx.setView(ctx.getDefaultView());

    ctx.draw(text);
    ctx.draw(blackness);
};
