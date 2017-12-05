#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "engine/Engine.hpp"

class GameEndScreen: public GameScreen
{
public:
    void init()
    {
        text.setString("Game Over");
        text.setFont(*ResourceManager::getFont("../resources/fonts/youmurderer.ttf"));
        text.setCharacterSize(100);
        sf::FloatRect pos = text.getLocalBounds();
        text.setPosition(720/2, 480/2);
        text.setOrigin(pos.left + pos.width / 2, pos.top + pos.height / 2); 
    };
    void onUpdate(float dt){};
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
    {
        ctx.setView(ctx.getDefaultView());
        ctx.draw(text);
    };
protected:
    sf::Text text;
    sf::Clock clock;
};