#include "engine/ResourceManager.hpp"
#include <iostream>

std::map<std::string, sf::Font> ResourceManager::fonts_cache;
std::map<std::string, sf::Texture> ResourceManager::textures_cache;
std::map< std::string, sf::SoundBuffer > ResourceManager::sound_cache;

sf::Font* ResourceManager::getFont(std::string name)
{
    if(!fonts_cache.count(name))
    {
        // load the fonts 
        sf::Font f;
        if(f.loadFromFile(name)){
            fonts_cache[name] = f;
        };
    }
    return &(fonts_cache[name]);
}

sf::SoundBuffer* ResourceManager::getSoundBuffer(std::string name)
{
    if(!sound_cache.count(name))
    {
        sf::SoundBuffer s;
        if(s.loadFromFile(name)){
            sound_cache[name] = s;
        }else{
            std::cout << "Sound " << name << " not found!" << std::endl;
        };
    }
    return &(sound_cache[name]);
}

sf::Texture* ResourceManager::getTexture(std::string name)
{
    if(!textures_cache.count(name))
    {
        sf::Texture t;
        if(t.loadFromFile(name)){
            textures_cache[name] = t;
        }else{
            std::cout << "Texture " << name << " not found!" << std::endl;
        };
    }
    return &(textures_cache[name]);
}