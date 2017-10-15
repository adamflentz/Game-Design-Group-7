#ifndef EVENTS_MANAGER_HPP
#define EVENTS_MANAGER_HPP
//////////////////////////
// Pretty Basic string based event manager
/////////////////////////
#include <queue>
#include <list>
#include <string>
#include <functional>

class BasicEvent
{
public:
    BasicEvent(){};
    BasicEvent(std::string m) : message(m){};
    std::string getMessage() {return message;};
private:
    std::string message;
};
// To access the two colliders the basic event must be
// casted to a GameObject(?)
// TODO: This kind of thing should be in another folder(?)
class CollisionEvent : public BasicEvent
{
public:
    // GameObject* coll1;
    // GameObject* coll2; 
};

class Events
{
public:
    static long addEventListener(std::function<void (BasicEvent)> listener);
    static void removeEventListener(long id);
    static void postEvent(BasicEvent e);
    static void notify();
private:
    static std::list<std::function<void (BasicEvent)>> listeners;
    static std::queue<BasicEvent> events;
};

#endif