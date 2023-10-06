#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class ScreenManager
{
public:
    ScreenManager();

    void setScreen(const std::string &screenName, const std::string &textureFile);
    void setCurrentScreen(const std::string &screenName);
    void drawCurrentScreen(sf::RenderWindow &window);

private:
    std::unordered_map<std::string, sf::Sprite> screens;
    std::string currentScreenName;
};
