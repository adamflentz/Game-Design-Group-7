#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/Engine.hpp"
#include "game/characters/Character.hpp"
<<<<<<< HEAD
#include "game/characters/Villain.hpp"
=======
>>>>>>> 72f383503a641408cc6a8c5925836ed9e38b6585
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
        void setGhost(std::shared_ptr<Villain> ghost) {g = ghost;};
        void setCharacter(std::shared_ptr<Character> activeChar) {c = activeChar;};
        void setCharacterList(std::vector<std::shared_ptr<Character>>* characterList) {charVector = characterList;};
        void setPlayerNumber(int number){playernumber = number;};
        void setTotalPlayers(int totalnumber){totalplayernumber = totalnumber;};
        void setRoomGroup(RoomGroup* g){this->rooms = g;};
    protected:
        RoomGroup* rooms;
        int playernumber;
        int totalplayernumber;
        std::shared_ptr<Villain> g;
        std::shared_ptr<Character> c;
        std::vector<std::shared_ptr<Character>>* charVector;
        sf::View v;
        void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
};