#include "engine/GameObject.hpp"

int GameObject::objectCount = 0;

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
    // give the gameObject an id
    o->objectID = "GameObject_" + std::to_string(objectCount);
    objectCount++;
    o->setParent(this);
    o->init();
    this->children.push_back(std::move(o));
}
// adds hitboxes
/*
void GameObject::addHitbox(Hitbox* h)
{

}
/**/
void GameObject::removeChild(GameObjectPtr o){}
void forEachChild(std::function<void()>& lambda){}