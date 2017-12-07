#ifndef EVENTS_MANAGER_HPP
#define EVENTS_MANAGER_HPP
//////////////////////////
// Pretty Basic string based event manager
/////////////////////////
#include <queue>
#include <list>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include "engine/EngineEvents.hpp"

// We have to use a shared_ptr to prevent object slicing
typedef std::shared_ptr<BasicEvent> base_event_type;
typedef std::list< std::function<void (base_event_type)> > event_list;

class Events
{
public:
    static long listener_id;
    static long addEventListener(std::string type, std::function< void (base_event_type) > listener);
    static void removeEventListener(long id);
    static void queueEvent(std::string, base_event_type e);
    // similar to post event except not added to a queue and immediately notifies
    static void triggerEvent(std::string, base_event_type e);
    static void clearAll(std::string s){
        listeners_map[s].clear();
    };
    static void clearEvent(){
        events = std::queue< base_event_type >();
    };
    static void notify();
private:
    static std::map< std::string, event_list > listeners_map;
    static std::queue< base_event_type > events;
};

#endif
