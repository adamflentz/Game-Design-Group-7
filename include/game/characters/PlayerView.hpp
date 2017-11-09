#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"
#include "game/characters/Character.hpp"
#include "game/rooms/RoomGroup.hpp"

////////////////
// PlayerView.hpp
// View used to follow characters around inside the game.  Should be able to create 4 
// views for 4 different players.  Will need to pull from Character to follow.
////////////////
class PlayerView: public GameObject 
{
    public:
        void init();
        void onUpdate(float dt);
        void setCharacter(std::shared_ptr<Character> activeChar) {c = activeChar;};
        void setCharacterList(std::vector<std::shared_ptr<Character>>* characterList) {charVector = characterList;};
        void setView(sf::FloatRect dimensions, sf::FloatRect viewport);
        void setPlayerNumber(int number){playernumber = number;};
        void setRoomGroup(RoomGroup* g){this->rooms = g;};
    protected:
        RoomGroup* rooms;
        int playernumber;
        std::shared_ptr<Character> c;
        std::vector<std::shared_ptr<Character>>* charVector;
        sf::View v;
        // Heads up display (Items, Health(?), etc)
        sf::View HUD;
        void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
};