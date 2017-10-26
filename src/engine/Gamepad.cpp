#include <iostream>
#include "engine/Gamepad.hpp"

void Gamepad::setLayout(LAYOUT layout)
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

int GamepadController::addGamepads(){
    std::cout << "Searching for Gamepads..." << std::endl;
    int count = 0;
    for(int i = 0; i < sf::Joystick::Count; i++){
        if(sf::Joystick::isConnected(i)){
            std::cout << "Gamepad found at index " << i << std::endl;
            gamepads[i] = Gamepad(i);

            count++;
        }
    }
    return count;
}

void GamepadController::removeGamepad(int id){
    
}