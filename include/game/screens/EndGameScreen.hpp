#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "engine/Engine.hpp"
// Very lazy file
class GameEndScreen: public GameScreen
{
public:
    void init()
    {
        clock.restart();
        // Reset some things
        this->showing = false;
        this->can_leave = false;
        // Game over string
        text.setString("Game Over");
        text.setFont(*ResourceManager::getFont("../resources/fonts/youmurderer.ttf"));
        text.setCharacterSize(100);
        sf::FloatRect pos = text.getLocalBounds();
        text.setPosition(720/2, 480/2);
        text.setOrigin(pos.left + pos.width / 2, pos.top + pos.height / 2); 
        // Press any button string
        press_any_button.setString("Press Any Button");
        press_any_button.setFont(*ResourceManager::getFont("../resources/fonts/youmurderer.ttf"));
        sf::FloatRect pos2 = press_any_button.getLocalBounds();
        press_any_button.setPosition(720/2, 480/2 + pos.top + pos.height + 20);
        press_any_button.setOrigin(pos2.left + pos2.width / 2, pos2.top + pos2.height / 2);
        
        Events::addEventListener("gamepad_event", [=](base_event_type e){
            auto gpe = dynamic_cast< GamepadEvent& >(*e);
            this->onGamepadEvent(gpe);
        });
    
    };
    void onUpdate(float dt){
        if(!showing && clock.getElapsedTime().asSeconds() >= delay){
            showing = true;
            can_leave = true;
        }
    };

    void onGamepadEvent(GamepadEvent gpe){
        if(gpe.type == GamepadEvent::RELEASED){
            if(can_leave){
                config->player_map.clear();
                config->char_map.clear();
                config->num_players = 1;
                auto event = std::make_shared< Event<std::string> >("Title");
                Events::clearAll("gamepad_event");
                Events::triggerEvent("change_screen", event);
            }
        }
    }

    void onDraw(sf::RenderTarget& ctx, sf::RenderStates states) const
    {
        ctx.setView(ctx.getDefaultView());
        ctx.draw(text);
        if(showing)
            ctx.draw(press_any_button);
    };
protected:
    sf::Text text;
    sf::Text press_any_button;
    sf::Clock clock;
    bool showing = false;
    bool can_leave = false;
    float delay = 3;  // Wait 4 seconds
};