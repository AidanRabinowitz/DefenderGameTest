#include "ScreenManager.h"
#include <iostream>

ScreenManager::ScreenManager() : currentScreenName("") {}

void ScreenManager::setScreen(const std::string &screenName, const std::string &textureFile)
{
    sf::Texture texture;
    sf::Sprite sprite;

    if (!texture.loadFromFile(textureFile))
    {
        std::cerr << "Couldn't load " << textureFile << std::endl;
        return;
    }

    sprite.setTexture(texture);

    // Scale the screen to fit the window
    float scaleX = static_cast<float>(sf::VideoMode::getDesktopMode().width) / texture.getSize().x;
    float scaleY = static_cast<float>(sf::VideoMode::getDesktopMode().height) / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);

    screens[screenName] = sprite;
}

void ScreenManager::setCurrentScreen(const std::string &screenName)
{
    currentScreenName = screenName;
}

void ScreenManager::drawCurrentScreen(sf::RenderWindow &window)
{
    auto it = screens.find(currentScreenName);
    if (it != screens.end())
    {
        window.draw(it->second);
    }
}
