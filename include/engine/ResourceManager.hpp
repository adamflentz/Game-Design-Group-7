#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class ResourceManager
{
public:
    static sf::Font* getFont(std::string name);
    static sf::Texture* getTexture(std::string name);
    static sf::SoundBuffer* getSoundBuffer(std::string name);
private:
    static std::map< std::string, sf::Font > fonts_cache;
    static std::map< std::string, sf::Texture > textures_cache;
    static std::map< std::string, sf::SoundBuffer > sound_cache;
};

#endif