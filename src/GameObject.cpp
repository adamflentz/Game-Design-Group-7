#include "engine/GameObject.hpp"

GameObject::GameObject()
{

}
// initiates update for all children
void GameObject::update(float dt)
{
    this->onUpdate(dt);
    for(auto a = this->children.begin(); a != this->children.end(); a++){
        // move the children relative to parent
        //(*a)->setPosition();
        (*a)->update(dt);
    }
}
// Initiates the render for all children
void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    this->onDraw(target, states);
    for(auto a = this->children.begin(); a != this->children.end(); a++){
        target.draw(**a, states);
    }
}
// adds children
void GameObject::addChild(GameObjectPtr o)
{
    o->init();
    this->children.push_back(std::move(o));
}
// adds hitboxes
/*
void GameObject::addHitbox(Hitbox* h)
{

}
/**/
void removeChild(){}
void forEachChild(std::function<void()>& lambda){}