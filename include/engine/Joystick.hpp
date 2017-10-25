#ifndef JOYSTICK_CONTROLS_HPP
#define JOYSTICK_CONTROLS_HPP

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
/*
* GameController that wraps the sf::Keyboard and sf::Joystick class.
* Useful for easily mapping common controller types (PS4/XBONE/KB&M)
* Can be modified to send events instead of being directly queried
* (may create overhead).
*/
class GameController
{
public:
    ControllerLayout controls;
    enum LAYOUT {GENERIC, PS4, XB1, XB360, KEYBOARD};
    void setController(int i){ controllerIndex = i; };
    void setLayout(LAYOUT layout); // lazily set a layout using enums
    void guessLayout(int cIndex);  // guess the controller layout(?)
protected:
    int controllerIndex = -1;
};

#endif