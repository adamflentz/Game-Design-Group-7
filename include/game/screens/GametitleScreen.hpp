#include <SFML/Graphics.hpp>
#include <memory>
#include "engine/Engine.hpp"


class GametitleScreen: public GameScreen
{
public:
    void init();
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
protected:
  // sf::Font font;
  // sf::Text t;
};
