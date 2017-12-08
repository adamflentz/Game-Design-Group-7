#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"
#include "game/characters/Character.hpp"
#include "game/characters/Villain.hpp"
#include "game/rooms/RoomGroup.hpp"
#include "components/EntityGroup.hpp"
#include "game/objects/Clue.hpp"

////////////////
// PlayerView.hpp
// View used to follow characters around inside the game.  Should be able to create 4
// views for 4 different players.  Will need to pull from Character to follow.
////////////////
class PlayerView: public GameObject
{
    public:
        PlayerView(){};
        void init();
        void onUpdate(float dt);
        // void setCharacter(std::shared_ptr<Character> activeChar) {c = activeChar;};
        // Pass a vector of entities by reference and the player's number (the entity the player shall control)
        void setEntities(EntityGroup* ents) {entity_group = ents;};
        // Set the dimensions and viewport of the view
        void setView(sf::FloatRect dimensions, sf::FloatRect viewport);
        sf::FloatRect viewDimensions;
        // Set the player's number (controls)
        void setEntityNumber(int number){playernumber = number;};

        // Set the controller index so we know which controller maps to this player
        void setControllerIndex(int index){};

        void setRoomGroup(RoomGroup* g){this->rooms = g;};
    protected:
        float viewport_x = 0;
        float viewport_y = 0;
        sf::Shader shader;
        sf::RectangleShape lighting;
        RoomGroup* rooms;
        int playernumber;
        // std::shared_ptr<Villain> g;
        // std::shared_ptr<Character> c;
        EntityGroup* entity_group;
        // std::vector<std::shared_ptr<Character>>& characters;
        sf::View v;
        // Heads up display (Items, Health(?), etc)
        sf::View HUD;
        sf::RectangleShape itemBar;
        sf::Texture heartTexture;
        sf::RectangleShape pain;
        void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Clock clock;
        int painCount;
};

#endif