#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <string>
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
    static int objectCount;

    typedef std::unique_ptr<GameObject> GameObjectPtr;
    GameObject();
    GameObject(sf::Vector2f p) : relPos(p) {};
    GameObject(int t, int l){relPos = sf::Vector2f(t, l);};
    // Virtual Methods
    // Not pure virtual, but you probably wanna still override these
    virtual void init(){};
    virtual void onUpdate(float dt){};
    virtual void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const{};
    // Adders
    void addChild(GameObjectPtr o);
    void addHitbox(GameObjectPtr h);
    // Removers
    void removeChild(GameObjectPtr o);
    void forEachChild(std::function<void()>& lambda);
    // updaters
    void relMove(int x, int y){ this->relPos += sf::Vector2f(x, y); };
    void relSetPosition(int x, int y){ this->relPos = sf::Vector2f(x, y); };
    void update(float dt);
    void checkHitboxes();
    // static methods
    std::list<GameObjectPtr> children;
protected:
    std::string objectID;
    // Relative position
    sf::Vector2f relPos{0, 0};
    // Parent GameObject
    GameObject* m_parent;
    std::list<GameObjectPtr> m_hitboxes;
    // inherited from sf::Drawable
    void setParent(GameObject* p){ this->m_parent = this; };
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif