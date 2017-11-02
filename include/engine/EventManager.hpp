#ifndef EVENTS_MANAGER_HPP
#define EVENTS_MANAGER_HPP
//////////////////////////
// Pretty Basic string based event manager
/////////////////////////
#include <queue>
#include <list>
#include <map>
#include <string>
#include <functional>

class BasicEvent
{
public:
    BasicEvent(){};
    BasicEvent(std::string m) : message(m){};
    std::string getMessage() {return message;};
    void setType(std::string t) { this->type = t; };
    std::string getType(){ return this->type; };
private:
    std::string type;
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

typedef std::list< std::function<void (BasicEvent)> > event_list;

class Events
{
public:
    static long listener_id;
    static long addEventListener(std::string type, std::function<void (BasicEvent)> listener);
    static void removeEventListener(long id);
    static void postEvent(std::string, BasicEvent e);
    static void notify();
private:
    static std::map< std::string, event_list > listeners_map;
    static std::queue<BasicEvent> events;
};

#endif
