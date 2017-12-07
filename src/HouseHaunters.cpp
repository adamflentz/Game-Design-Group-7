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
    config = std::make_shared<Config>();
    this->setName("House Haunters");
    // Setup the window position and dimensions
    this->setWindowRect(100, 100, config->width, config->height);
    // Initialize the game screendisableGamepads
    std::unique_ptr<GameScreen> screen_gamestory = std::unique_ptr<GameScreen>(new GamestoryScreen());
    screen_gamestory->setConfig(config);
    std::unique_ptr<GameScreen> screen_gameplay  = std::unique_ptr<GameScreen>(new GameplayScreen());
    screen_gameplay->setConfig(config);
    std::unique_ptr<GameScreen> screen_gametitle = std::unique_ptr<GameScreen>(new GametitleScreen());
    screen_gametitle->setConfig(config);
    std::unique_ptr<GameScreen> screen_character = std::unique_ptr<GameScreen>(new CharacterScreen());
    screen_character->setConfig(config);
    std::unique_ptr<GameScreen> screen_end = std::unique_ptr<GameScreen>(new GameEndScreen());
    screen_end->setConfig(config);
    // Add the game screen
    // since it's a unique pointer we have to move it firstdisableGamepads
    this->addGameScreen("Story",     std::move(screen_gamestory) );
    this->addGameScreen("Title",     std::move(screen_gametitle) );
    this->addGameScreen("Character", std::move(screen_character) );
    this->addGameScreen("GamePlay",  std::move(screen_gameplay) );
    this->addGameScreen("GameEnd",   std::move(screen_end) );

    // start off at title screen
    this->changeGameScreen("Story");
}
