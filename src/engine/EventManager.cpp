#include "engine/EventManager.hpp"

// define static members
long Events::listener_id = 0;
std::map< std::string, event_list > Events::listeners_map;
std::queue<BasicEvent> Events::events;

long Events::addEventListener(std::string type, std::function<void (BasicEvent)> listener)
{ 
    // if event type not in map, add it (?)
    if(listeners_map.count(type) == 0) 
        listeners_map[type] = event_list(); 
    listeners_map[type].push_back(listener);
    // not sure where to put this id yet
    // maybe make the listener's map a map too(?)
    return listener_id++;
};

void Events::postEvent(std::string type, BasicEvent e)
{ 
    e.setType(type);
    events.push(e);
};

void Events::notify()
{
    while(!events.empty()) {
        // get event in front
        auto e = events.front();
        std::string type = e.getType();
        if(listeners_map.count(type) == 1){
            // iterate through listeners for that type
            auto list = listeners_map[type];
            for(auto it = list.begin(); it != list.end(); it++){
                // call function with event
                (*it)(e);
            }
        }else{
            // fail silently b/c no event listeners(?)
        }
        // go on to the next event
        events.pop();
    }
};

void Events::removeEventListener(long id)
{
    
};