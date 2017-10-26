#ifndef JOYSTICK_CONTROLS_HPP
#define JOYSTICK_CONTROLS_HPP
///////////
// A very rough layout of how we might
// decide to extrapolate the joystick controls
//
////////////
#include <SFML/Graphics.hpp>

struct ControllerLayout
{
    int up;
    int down;
    int left;
    int right;

    int button0;
    int button1;
    int button2;
    int button3;
};

class Gamepad
{
public:
    Gamepad(){};
    Gamepad(int index) : controllerIndex(index) { this->guessLayout(); };
    ControllerLayout controls;
    enum LAYOUT {GENERIC, PS4, PS3, XB1, XB360, KEYBOARD};
    void setController(int i){ controllerIndex = i; };
    // set layout based on enum values
    void setLayout(LAYOUT layout);
protected:
    // guess the controller layout by checking vendor id/name
    LAYOUT guessLayout();
    int controllerIndex = -1;
};

class GamepadController
{
public:
    int addGamepads();                           // add a gamepad and  return the id of added gamepad 
    void removeGamepad(int id);
    void disableGamepads(std::vector<int> ids); // Disable 0 or more gamepads
    void enableGamepads(std::vector<int> ids);  // Disable 1 or more gamepads
    Gamepad* getGamepad(int index);
    // Query button presses(?)
    void update();
private:
    // list of game controllers
    std::map<int, Gamepad> gamepads;
};

#endif