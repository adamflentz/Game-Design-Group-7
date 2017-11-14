#ifndef ENGINE_EVENTS_HPP
#define ENGINE_EVENTS_HPP

#include <string>

class BasicEvent{
public:
    BasicEvent(){};
    virtual ~BasicEvent(){};
    std::string getEventType(){ return this->eventType; };
    void setEventType(std::string t) { this->eventType = t; };
protected:
    std::string eventType;
};

template< class Data_T >
class Event : public BasicEvent
{
public:
    Event(Data_T d){ this->data = d; };
    Data_T data;
};

#endif