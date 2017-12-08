#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "engine/Engine.hpp"

class EndGameScreen: public GameScreen
{
public:
    void init();
    void onUpdate(float dt);
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;

protected:
    sf::Text text;
    sf::Clock clock;
    sf::Sound over;
    int trans = 255;
    sf::RectangleShape blackness;
};
