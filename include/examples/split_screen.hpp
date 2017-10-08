#ifndef SPLITSCREEN_HPP
#define SPLITSCREEN_HPP

#include <memory>
#include "engine/GameObject.hpp"
#include "engine/Game.hpp"

class WorldMap: public GameObject
{
public:
    void init();
    void onDraw(sf::RenderTarget& ctx) const;
protected:
    sf::Texture mapTexture;
    sf::Sprite map;
};

class Player: public GameObject
{
public:
    struct KEYS {
        sf::Keyboard::Key up = sf::Keyboard::Up;
        sf::Keyboard::Key down = sf::Keyboard::Down;
        sf::Keyboard::Key left = sf::Keyboard::Left;
        sf::Keyboard::Key right = sf::Keyboard::Right;
    } controls;
    sf::Color color = sf::Color::Red;
    void setView(sf::View* v) { this->view = v; };
    void init();
    void onUpdate(float dt);
    void onDraw(sf::RenderTarget& ctx) const;
protected:
    float charSpeed = 250.0f; // in pixels per second
    sf::View* view; // a view that follows the player
    sf::CircleShape character;
    //void onUpdate(int dt);
};

class MenuScene: public GameScene
{
public:
    void init();
};

class PlayScene: public GameScene
{
public:
    void init();
protected:
    std::unique_ptr<Player> Player1;
    std::unique_ptr<Player> Player2;
    sf::View p1View;
    sf::View p2View;
    std::unique_ptr<WorldMap> m;
};

class SplitScreenGame: public GameEngine
{
public:
    void init();
private:
    std::unique_ptr<GameScene> playscene; 

};

#endif