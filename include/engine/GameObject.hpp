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
    // Virtual Methods
    virtual void init(){};
    virtual void onUpdate(float dt){};
    virtual void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const{};
    // Adders
    void addChild(GameObjectPtr o);
    // Removers
    void removeChild();
    void forEachChild(std::function<void()>& lambda);
    void update(float dt);
    sf::Vector2f velocity{0, 0};
protected:
    GameObject* parent;
    std::list<GameObjectPtr> children;
    /*std::list< Hitbox* > m_hitboxes;/**/
    /*void drawHitboxes(sf::RenderWindow* ctx);/**/
    void setParent(GameObject* o);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif