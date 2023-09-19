#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Humanoid.h"
class Player : public sf::Sprite
{
public:
    Player();
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    void setTexture(const sf::Texture &texture);
    void setScale(const sf::Vector2f &factors);
    void render(sf::RenderWindow &window) const;
    const sf::Vector2f &getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    bool isTouchingHumanoid(const Humanoid &humanoid) const;

private:
    sf::Sprite sprite;
};

#endif // PLAYER_H
