#include <iostream>
#include "engine/Gamepad.hpp"

void Gamepad::setLayout(LAYOUT layout)
{
    this->layout = layout;
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
            controls = {
                12, 
                13,
                14,
                15,
                0,
                1,
                2,
                3
            };
            break;
        case LAYOUT::XB360:
        case LAYOUT::XB1:
            break;
        case LAYOUT::GENERIC:
            break;
    };
}

Gamepad::LAYOUT Gamepad::guessLayout()
{
    // If no index for this gamepad, fail soft(?)
    if(controllerIndex < 0)
        return LAYOUT::GENERIC;

    std::cout << "Guessing Layout for controller at index " << controllerIndex << std::endl;

    sf::Joystick::Identification id = sf::Joystick::getIdentification(controllerIndex);

    switch(id.vendorId){
        // Playstation
        case 0x054c:
            switch(id.productId){
                case 0x05c4: // ps4 conroller
                    std::cout << "PS4 Controller(?)" << std::endl;
                    return LAYOUT::PS4;
                    break;
            }
            break;
        // Microsoft
        case 0x045e:
            switch(id.productId){
                case 0x02ea:
                    std::cout << "XBONE Controller(?)" << std::endl;
                    return LAYOUT::XB1;
                    break;
            }
            break;
        default:
            std::cout << "Couldn't Determine Specific Controller" << std::endl;
            return LAYOUT::GENERIC;
            break;
    }
}

void Gamepad::update()
{
    if(!sf::Joystick::isConnected(controllerIndex)){
        std::cout << "Gamepad disconnected from index " << controllerIndex << std::endl;
    }else{
        // sfml treats the d-pad as an axis for some reason
        float povx = sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX);
        float povy = sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovY);

        if(povx == 100){
            std::cout << "RIGHT BUTTON PRESSED " << std::endl;
        }
        else if (povx == -100)
        {
            std::cout << "LEFT BUTTON PRESSED" << std::endl;
        }
        else
        {

        }

        if(povy == -100){
            std::cout << "UP BUTTON PRESSED " << std::endl;
        }
        else if (povy == 100)
        {
            std::cout << "DOWN BUTTON PRESSED" << std::endl;
        }
        else
        {

        }

        for(int i = 0; i < sf::Joystick::getButtonCount(controllerIndex); i++){
            if(sf::Joystick::isButtonPressed(controllerIndex, i)){
                std::cout << i << " BUTTON PRESSED " << std::endl; 
            }
        }
    }
}

int GamepadController::addGamepads()
{
    // Make sure connected joysticks up to date 
    sf::Joystick::update(); 
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

void GamepadController::removeGamepad(int id)
{
    
}

void GamepadController::update()
{
    for(auto it = gamepads.begin(); it != gamepads.end(); it++){
        (*it).second.update();
    }
}