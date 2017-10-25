#include <iostream>
#include "engine/Joystick.hpp"

void GameController::setLayout(LAYOUT layout)
{
    switch(layout){
        case LAYOUT::KEYBOARD:
            controls = {
                sf::Keyboard::Up, 
                sf::Keyboard::Down,
                sf::Keyboard::Left,
                sf::Keyboard::Right,
                sf::Keyboard::Z,
                sf::Keyboard::X,
                sf::Keyboard::C,
                sf::Keyboard::V
            };
            break;
        case LAYOUT::PS4:
            break;
        case LAYOUT::XB360:
        case LAYOUT::XB1:
            break;
        case LAYOUT::GENERIC:
            break;
    };
}