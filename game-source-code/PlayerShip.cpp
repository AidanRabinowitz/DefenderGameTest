#include "PlayerShip.h"
#include "PlayerLaser.h"
#include <SFML/Graphics.hpp>

PlayerShip::PlayerShip(sf::Vector2f position) : shipSize(50.f, 50.f), speed(200.f)
{
    ship.setFillColor(sf::Color::Green);
    ship.setSize(shipSize);
    ship.setPosition(position);
    ship.setOrigin(shipSize / 2.f);
}
sf::Vector2f PlayerShip::getPosition() const
{
    return ship.getPosition();
}

void PlayerShip::update(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && ship.getPosition().x > 0.f)
    {
        ship.move(-speed * deltaTime, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && ship.getPosition().x + ship.getSize().x < 800.f)
    {
        ship.move(speed * deltaTime, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && ship.getPosition().y > 0.f)
    {
        ship.move(0.f, -speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ship.getPosition().y + ship.getSize().y < 600.f)
    {
        ship.move(0.f, speed * deltaTime);
    }

    for (size_t i = 0; i < lasers.size(); ++i)
    {
        lasers[i].move(speed * deltaTime, 0.f);

        if (lasers[i].getPosition().x > 800.f)
        {
            lasers.erase(lasers.begin() + i);
            --i;
        }
    }
}

void PlayerShip::fireLaser(std::vector<PlayerLaser> &lasers)
{
    lasers.push_back(PlayerLaser(ship.getPosition() + sf::Vector2f(0.f, -shipSize.y / 2.f)));
}

void PlayerShip::draw(sf::RenderWindow &window)
{
    window.draw(ship);

    for (const PlayerLaser &laser : lasers)
    {
        laser.draw(window);
    }
}

void PlayerShip::handleMouseClick(const sf::Event &event, std::vector<PlayerLaser> &lasers)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        fireLaser(lasers);
    }
}
