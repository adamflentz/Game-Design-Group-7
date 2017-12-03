#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "engine/Engine.hpp"

class CharacterIcon : public GameObject 
{
public:
    void init(){};
    void setColor(sf::Color color){ t.setFillColor(color);};
    void setFont(std::string font){ t.setFont(*ResourceManager::getFont(font)); };
    void setPlayer(int num){ player_number = num; t.setString("P"+std::to_string(num)); };
    int  getPlayer(){return player_number; };
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
protected:
    int player_number = -1;
    sf::Text t;
};


class CharacterSelection : public GameObject
{
public:
    void init(){};
    void setPortraitTexture(std::string texture);
    void setPlayer(int player){player_selected = player; selected = true; };
    void unsetPlayer(){player_selected = -1; selected = false; };
    int  getPlayer(){ return player_selected; };
    bool isSelected(){ return selected; };
    void removePlayer(int num);
    void addPlayer(int num);
    bool hasPlayer(int num);
    bool isEmpty(){ return hovering.size() == 0; };
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
    void onUpdate(float dt);
    void moveRight(int num);
protected:
    sf::Color colors[4] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};
    std::vector<std::unique_ptr<CharacterIcon>>::iterator find(int player);
    bool selected = false;
    int player_selected = -1;
    sf::Sprite portrait;
    std::vector<std::unique_ptr<CharacterIcon>> hovering;
};


class CharacterScreen: public GameScreen
{
public:
    void init();
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
    void onUpdate(float dt);
protected:
    void onGamepadEvent(GamepadEvent e);
    void addPlayer(int num, int index);
    std::vector<std::unique_ptr<CharacterSelection>> char_selections;
    std::vector<std::unique_ptr<sf::Text>> texts;
    bool changed;
    sf::RectangleShape background;
    sf::Text teamFont;
    sf::Texture title;
    sf::RectangleShape blackness;
    int player_num = 1;
    int trans = 255;
    int selected_count = 0;
};
