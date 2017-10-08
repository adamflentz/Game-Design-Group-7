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
    //friend class GameEngine;
    typedef std::unique_ptr<GameObject> GameObjectPtr;
    GameObject();
    virtual void init(){};
    virtual void onUpdate(float dt){};
    virtual void onDraw(sf::RenderTarget& ctx/*, sf::RenderStates states/**/) const{};
    /*void addHitbox(AbstractHitbox h);/**/
    void addChild(GameObjectPtr o);
    void removeChild();
    void forEachChild(std::function<void()>& lambda);
    /*void setGame(GameEngine* g){ game = g; };*/
    void update(float dt);
protected:
    GameObject* parent;
    //GameEngine* game;
    std::list<GameObjectPtr> children;
    /*std::list<AbstractHitbox> hitboxes;/**/
    void updateHitboxes(); // recalculate relative hitbox positions
    /*void drawHitboxes(sf::RenderWindow* ctx);/**/
    void setParent(GameObject* o);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif