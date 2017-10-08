#ifndef EVENTS_MANAGER_HPP
#define EVENTS_MANAGER_HPP
//////////////////////////
// This file is incomplete
// 
/////////////////////////
#include "engine/GameObject.hpp"

class BasicEvent
{
public:
    std::unique_ptr<GameObject> getEventObject();
private:
    std::unique_ptr<GameObject> target;
};

class EventListener
{
    public:
        virtual void onEvent(BasicEvent e) = 0;
};

// publish/subscribe 
class EventManager
{
public:
    enum EVENT_TYPE {KEYDOWN, KEYUP, MOUSEDOWN};
    void addEventListener();
private:
    std::vector<std::shared_ptr<EventHandler>> key_pressed;
};

#endif