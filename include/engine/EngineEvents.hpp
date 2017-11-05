#ifndef ENGINE_EVENTS_HPP
#define ENGINE_EVENTS_HPP

#include <string>

class BasicEvent{
public:
    BasicEvent(){};
    virtual ~BasicEvent(){};
    std::string getType(){ return this->type; };
    void setType(std::string t) { this->type = t; };
protected:
    std::string type;
};

template< class Data_T >
class Event : public BasicEvent
{
public:
    Event(Data_T d){ this->data = d; };
    Data_T data;
};

#endif