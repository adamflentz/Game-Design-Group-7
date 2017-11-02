#include <iostream>
#include "engine/GameEngine.hpp"

void GameEngine::start()
{
    // initialize game
    this->init();
    // create window
    window.create(sf::VideoMode(this->winDim.width, this->winDim.height), this->name, sf::Style::Titlebar | sf::Style::Close);
    this->running = true;
    // create clock
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    // This will limit the game to 60fps
    // It's hardcoded for now, but we should change it...
    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    // main game loop
    while(window.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        this->handleEvents();
        while(timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            // maybe instead pass in timePerFrame as sf::Time
            this->update(timePerFrame.asSeconds());
        }
        this->draw();
        // update game statistics (running time, framerate, etc...)
        /*this->updateStats();/**/
    }
    this->running = false;
}

void GameEngine::update(float dt)
{
    if(this->currScene)
    {
        this->currScene->update(dt);
    }
}

void GameEngine::draw()
{
    window.clear(sf::Color::Black);
    if(this->currScene)
    {
        window.draw(*(this->currScene));
    }
    window.display();
}
void GameEngine::addGameScreen(std::string id, std::unique_ptr<GameScreen> s)
{
  s->setEngine(this);
  screens[id] = std::move(s);

}
void GameEngine::changeGameScreen(std::string s)
{
    bool canChange = true;
    std::cout << "changing screen" << std::endl;
    if(this->currScene)
    {
        bool canChange = this->currScene->onExit();
    }

    if(canChange)
    {
        this->currScene = screens[s].get();
        if(this->currScene)
        {
            //this->currScene->setGame(this);
            this->currScene->init();
        }
    }
}

void GameEngine::handleEvents()
{
    //mousePos = sf::Mouse::getPosition(window);
    // process events
    // TODO: Move to another function
    sf::Event Event;
    while(window.pollEvent(Event))
    {
        switch(Event.type)
        {
            case sf::Event::Closed:
                this->exit();
                break;
            //case sf::Event::MouseButtonReleased:
                //this->ebus.postEvent(BasicEvent("MOUSEUP", mousePos.x, mousePos.y));
            //    break;
        }
    }

    // notify of all events that took place last frame
    Events::notify();
}
/**
* Gives you a chance to prevent the game from exiting and/or do
* some cleanup before the window closes
*/
void GameEngine::exit()
{
    bool canExit = this->onExit();
    if(canExit)
    {
        this->window.close();
    }
}
