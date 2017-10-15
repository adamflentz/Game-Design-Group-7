#include "engine/EventManager.hpp"

void EventManager::addEventListener(std::function<void (BasicEvent)> listener)
{ 
    listeners.push_back(listener); 
};

void EventManager::postEvent(BasicEvent e)
{ 
    events.push(e); 
};

void EventManager::notify()
{
    while(!events.empty()) {
        for (auto l = listeners.begin(); l != listeners.end(); l++) {
            (*l)(events.front());
        }
        events.pop();
    }
};

void EventManager::removeEventListener(long id)
{

};