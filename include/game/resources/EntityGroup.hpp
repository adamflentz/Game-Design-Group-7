#ifndef ENTITYLIST_HPP
#define ENTITYLIST_HPP

#include "engine/Engine.hpp"
#include "components/SpriteAnimation.hpp"
#include "components/Hitbox.hpp"
#include <list>

class EntityGroup: public GameObject
{
public:
   bool isColliding(sf::FloatRect hbox);
   std::list<std::shared_ptr<GameObject>> EntityList;
protected:
};

#endif
