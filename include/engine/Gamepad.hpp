#ifndef JOYSTICK_CONTROLS_HPP
#define JOYSTICK_CONTROLS_HPP
///////////
// A very rough layout of how we might
// decide to extrapolate the joystick controls
//
////////////
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "engine/EventManager.hpp"
#include "engine/EngineEvents.hpp"

class GamepadEvent : public BasicEvent
{
public:
    enum TYPE {PRESSED, RELEASED, DISCONNECT, CONNECT};
    int index;
    TYPE type;
    std::string button;
};

typedef struct {
    int button;
    bool isDown;    
} BUTTON_S;

typedef struct {
    sf::Keyboard::Key button;
    bool isDown;
} KBUTTON_S;

class Gamepad
{
public:
    Gamepad(){};
    Gamepad(int index) : controllerIndex(index) { setLayout(guessLayout()); };
    enum LAYOUT {GENERIC, PS4, PS3, XB1, XB360, KEYBOARD};
    // some setters
    void setController(int i){ controllerIndex = i; setLayout(guessLayout()); };
    void setIndex(int i){ this->controllerIndex = i; };
    void setActive(bool a){ this->isActive_b  = a; };
    // set layout based on enum values
    void setLayout(LAYOUT layout);
    // some getters
    LAYOUT getLayout(){ return layout; };
    bool isConnected(){ return this->isConnected_b; };
    bool isActive(){ return this->isActive_b; };

    void update();
    int playerIndex = -1;
protected:
    // guess the controller layout by checking vendor id/name
    LAYOUT guessLayout();
    // layout
    LAYOUT layout;
    int controllerIndex = -1;
    std::map<std::string, BUTTON_S> button_map;
    std::map<std::string, KBUTTON_S> kbutton_map; // for keyboards b/c 
    bool isConnected_b = true;
    bool isActive_b = true;
};

class GamepadController
{
public:
    int addGamepads();                           // add a gamepad and  return the id of added gamepad 
    void removeGamepad(int id);
    void disableGamepads(std::vector<int> ids); // Disable 0 or more gamepads
    void enableGamepads(std::vector<int> ids);  // Disable 1 or more gamepads
    Gamepad* getGamepad(int index){return &gamepads[index]; };
    int count = 0;
    // Query button presses(?)
    void update();
private:
    // list of game controllers ordered by 
    std::map<int, Gamepad> gamepads;
};

#endif