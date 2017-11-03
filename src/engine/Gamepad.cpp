#include <iostream>
#include "engine/Gamepad.hpp"

void Gamepad::setLayout(LAYOUT layout)
{

    this->layout = layout;
    switch(layout){
        case LAYOUT::KEYBOARD:
            button_map["A"] = BUTTON_S{sf::Keyboard::Z, false};
            button_map["B"] = BUTTON_S{sf::Keyboard::X, false};
            button_map["X"] = BUTTON_S{sf::Keyboard::C, false};
            button_map["Y"] = BUTTON_S{sf::Keyboard::V, false};
            break;
        case LAYOUT::PS4:
            button_map["A"]     = BUTTON_S{1,  false};
            button_map["B"]     = BUTTON_S{2,  false};
            button_map["Y"]     = BUTTON_S{3,  false};
            button_map["X"]     = BUTTON_S{0,  false};
            button_map["UP"]    = BUTTON_S{-1, false};
            button_map["LEFT"]  = BUTTON_S{-1, false};
            button_map["RIGHT"] = BUTTON_S{-1, false};
            button_map["DOWN"]  = BUTTON_S{-1, false};
            break;
        case LAYOUT::XB360:
        case LAYOUT::XB1:
            break;
        case LAYOUT::GENERIC:
        default:
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
    if(this->layout == LAYOUT::KEYBOARD || !sf::Joystick::isConnected(controllerIndex)){
        // std::cout << "Gamepad disconnected from index " << controllerIndex << std::endl;
    }else{
        // sfml treats the d-pad as an axis for some reason
        float povx = sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX);
        float povy = sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovY);

        for (auto it = button_map.begin(); it != button_map.end(); it++)
        {
            std::string button = it->first;
            bool isPressed = false;
            // special cases for up, down, left, and right
            if( (button == "UP" && povy == -100)    || 
                (button == "DOWN" && povy == 100)   ||
                (button == "LEFT" && povx == -100)   || 
                (button == "RIGHT" && povx == 100)  
            )
                isPressed = true;
            else{
                if(it->second.button >= 0)
                    isPressed = sf::Joystick::isButtonPressed(controllerIndex, it->second.button);
            }
            bool wasPressed = it->second.isDown; 
            if( isPressed && !wasPressed ) // if button pressed, but not already pressed
            {
                // send button pressed event
                std::cout << button << " Button Pressed" << std::endl;
                it->second.isDown = true;
            }
            else if(!isPressed && wasPressed)
            {
                // send button released event
                std::cout << it->first << " Button Released" << std::endl;
                it->second.isDown = false;
            }
            else if(!isPressed)
            {
                it->second.isDown = false;
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
            // find any available gamepad slot
            gamepads[i] = Gamepad(i);
            count++;
        }
    }

    // default last gamepad to keyboard
    gamepads[count] = Gamepad();
    gamepads[count].setLayout(Gamepad::LAYOUT::KEYBOARD);

    return count;
}

void GamepadController::removeGamepad(int id)
{
    
}

void GamepadController::update()
{
    // try to determine disconnects and connects
    // update controller
    for(auto it = gamepads.begin(); it != gamepads.end(); it++){
        (*it).second.update();
    }
}