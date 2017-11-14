#include <SFML/Graphics.hpp>
#include <memory>
#include "engine/Engine.hpp"


class GametitleScreen: public GameScreen
{
public:
    void init();
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
    void onUpdate(float dt);
protected:
    sf::Sprite sprite;
    sf::Texture title;
    sf::RectangleShape blackness;
    int trans = 255;
  // sf::Font font;
  // sf::Text t;
};
