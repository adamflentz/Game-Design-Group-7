#include "engine/EventManager.hpp"

void Events::addEventListener(std::function<void (BasicEvent)> listener)
{ 
    listeners.push_back(listener); 
};

void Events::postEvent(BasicEvent e)
{ 
    events.push(e); 
};

void Events::notify()
{
    while(!events.empty()) {
        for (auto l = listeners.begin(); l != listeners.end(); l++) {
            (*l)(events.front());
        }
        events.pop();
    }
};

void Events::removeEventListener(long id)
{

};