#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "engine/Engine.hpp"

class EndGameScreen: public GameScreen
{
public:
    void init();

    void onUpdate(float dt);

    void onGamepadEvent(GamepadEvent gpe);

    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;

protected:
    sf::Text text;
    sf::Text press_any_button;
    sf::Clock clock;

    bool showing = false;
    bool can_leave = false;
    float delay = 3;  // Wait 4 seconds

    sf::Sound over;
    int trans = 255;
    sf::RectangleShape blackness;
};
