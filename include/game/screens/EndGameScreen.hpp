class GameplayScreen: public GameScreen
{
public:
    void init();
    void onUpdate(float dt);
    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const;
protected:
    sf::Text text;
    sf::Clock clock;
}