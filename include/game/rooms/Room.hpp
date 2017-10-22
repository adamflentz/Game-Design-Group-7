#include "engine/Engine.hpp" 
#include <SFML/Graphics.hpp>

class Room: public GameObject
{
public:
    void init();
    void CreateRoom();
    void setRoomPosition(int x, int y);
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::RectangleShape rect;
};