#include "game/resources/EntityGroup.hpp"

bool EntityGroup::isColliding(sf::FloatRect hbox){
    for(auto a = EntityList.begin(); a != EntityList.end(); a++){
        return false;
    }
    return false;
}