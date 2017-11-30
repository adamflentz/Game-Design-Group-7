#include "engine/Engine.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/Hitbox.hpp"
#include "game/characters/Character.hpp"
#include <list>

class CharacterGroup: public GameObject
{
public:
    std::vector<std::shared_ptr<Character>> CharacterList;
    bool isColliding(sf::FloatRect hbox);
};