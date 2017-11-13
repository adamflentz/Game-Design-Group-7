#include "HouseHaunters.hpp"
#include <iostream>

////////////////////////
// HouseHaunters.cpp
//
// This is where we perform our game setup. You can do things like add game screens
// create
//
// Next check out the file include/game/screens/GameplayScreen.hpp
///////////////////////

void HouseHauntersGame::init()
{
    // Setup the window position and dimensions
    this->setWindowRect(100, 100, 720, 480);
    // Initialize the game screen
    std::unique_ptr<GameScreen> screen_gameplay  = std::unique_ptr<GameScreen>(new GameplayScreen());
    std::unique_ptr<GameScreen> screen_gametitle = std::unique_ptr<GameScreen>(new GametitleScreen());
    // Add the game screen
    // since it's a unique pointer we have to move it first
    this->addGameScreen("Title", std::move(screen_gametitle) );
    this->addGameScreen("GamePlay", std::move(screen_gameplay) );

    // start off at title screen
    this->changeGameScreen("Title");

    PlantSeeds(-1);
    ClueReader reader;
    reader.readFile("../resources/items.xml");
    reader.selectItems();
}
