#include <iostream> 
// world map
void WorldMap::init()
{
    mapTexture.loadFromFile("../resources/textures/basic.png");
    map.setTexture(mapTexture);
}
void WorldMap::onDraw(sf::RenderTarget& ctx) const
{
    ctx.draw(map);
}
// player
void Player::init()
{
    std::cout << "Initializing Player" << std::endl;
    character.setRadius(25);
    character.setFillColor(this->color);
    character.setPosition(this->getPosition());
}
void Player::onUpdate(float dt)
{
    if(sf::Keyboard::isKeyPressed(this->controls.up))
    {
        this->view->move(0, -(this->charSpeed) * dt);
        this->move(0, -(this->charSpeed) * dt);
    }
    else if(sf::Keyboard::isKeyPressed(this->controls.down))
    {
        this->view->move(0, (this->charSpeed) * dt);
        this->move(0, (this->charSpeed) * dt);
    }

    if(sf::Keyboard::isKeyPressed(this->controls.left))
    {
        this->view->move(-(this->charSpeed) * dt, 0);
        this->move(-(this->charSpeed) * dt, 0);
    }
    else if(sf::Keyboard::isKeyPressed(this->controls.right))
    {
        this->view->move((this->charSpeed) * dt, 0);
        this->move((this->charSpeed) * dt, 0);
    }
    character.setPosition(this->getPosition());
}

void Player::onDraw(sf::RenderTarget& ctx) const
{
    ctx.draw(character);
}
// play screen
void PlayScene::init()
{

    std::cout << "Initializing Scene" << std::endl;
    // setup player 1
    Player1 = std::unique_ptr<Player>(new Player()); // tfw no make_unique in C++1 T_T
    Player1->setPosition(400, 400);
    Player1->setOrigin(25, 25);
    Player1->controls.up = sf::Keyboard::W;
    Player1->controls.down = sf::Keyboard::S;
    Player1->controls.left = sf::Keyboard::A;
    Player1->controls.right = sf::Keyboard::D;
    Player1->color = sf::Color::White;
    // setup player 2 (with different controls)
    Player2 = std::unique_ptr<Player>(new Player());
    Player2->setPosition(700, 700);
    Player2->setOrigin(25, 25);
    Player2->color = sf::Color::Blue;
    // setup two views
    p1View.setSize(sf::Vector2f(400, 600)); // half the window width
    p1View.setCenter(Player1->getPosition() + Player1->getOrigin());
    p1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1)); //p1 on the left

    p2View.setSize(sf::Vector2f(400, 600)); // half the window width
    p2View.setCenter(Player2->getPosition() + Player2->getOrigin());
    p2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1)); // p2 on the right
    // add views to the scene
    this->addView(&p1View);
    this->addView(&p2View);
    // let the player manage their view 
    Player1->setView(&p1View);
    Player2->setView(&p2View);
    // setup map
    m = std::unique_ptr<WorldMap>(new WorldMap());
    // add p1 and p2 to the scene
    this->addChild(std::move(m));
    this->addChild(std::move(Player1));
    this->addChild(std::move(Player2));
}
// split screen game
void SplitScreenGame::init()
{
    std::cout << "Initializing Game" << std::endl;
    playscene = std::unique_ptr<GameScene>(new PlayScene());
    this->changeGameScene(std::move(playscene));
}