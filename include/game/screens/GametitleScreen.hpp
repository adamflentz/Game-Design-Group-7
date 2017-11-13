#include <SFML/Graphics.hpp>
#include <memory>
#include "engine/Engine.hpp"


class GametitleScreen: public GameScreen
{
public:
    void init();
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
protected:
    sf::Sprite sprite;
    sf::Texture title;
  // sf::Font font;
  // sf::Text t;
};
