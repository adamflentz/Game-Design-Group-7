#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <list>

////////////////////////////////
//
//
//
///////////////////////////////
class GameObject: public sf::Transformable, public sf::Drawable
{
public:
    typedef std::unique_ptr<GameObject> GameObjectPtr;
    GameObject();
    GameObject(sf::Vector2f p) : relPos(p) {};
    GameObject(int t, int l){relPos = sf::Vector2f(t, l);};
    // Virtual Methods
    virtual void init(){};
    virtual void onUpdate(float dt){};
    virtual void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const{};
    // Adders
    void addChild(GameObjectPtr o);
    // Removers
    void removeChild();
    void forEachChild(std::function<void()>& lambda);
    // updaters
    void relMove(int x, int y){ this->relPos += sf::Vector2f(x, y); };
    void relSetPosition(int x, int y){ this->relPos = sf::Vector2f(x, y); };
    void update(float dt);
    sf::Vector2f velocity{0, 0};
protected:
    /*void follow/**/
    // Relative position
    sf::Vector2f relPos;
    GameObject* parent;
    std::list<GameObjectPtr> children;
    /*std::list< Hitbox* > m_hitboxes;/**/
    /*void drawHitboxes(sf::RenderWindow* ctx);/**/
    void setParent(GameObject* o);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif