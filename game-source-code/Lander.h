#pragma once

#include <SFML/Graphics.hpp>
#include "GameConstants.h" // Include your game constants here
#include "Humanoid.h"

class Humanoid;

class Lander
{
public:
    Lander();
    void reset();
    void update();
    void render(sf::RenderWindow &window);
   
    sf::Vector2f getPosition() const;

    sf::Sprite &getSprite();
    bool isDestroyed() const;
    sf::Sprite landerSprite;
    sf::Texture landerTexture;
    void destroy();
    void attachToHumanoid(Humanoid *humanoid); // Attach the Lander to a Humanoid
    bool isAttached() const;                   // Check if the Lander is attached to a Humanoid
    void moveLanderUp();
     // Public member variable to store the velocity
    sf::Vector2f velocity;

    sf::Vector2f getVelocity() const; // Declaration of getVelocity function

    Humanoid *attachedHumanoid;

     // Function to attach a humanoid to the lander
    void attachHumanoid(Humanoid *humanoid);

    // Function to check if the lander is carrying a humanoid
    bool isCarryingHumanoid() const;

    // Function to get the abducted humanoid (if any)
    Humanoid* getAbductedHumanoid() const;
    

private:
    bool destroyed;

    // Pointer to the humanoid currently abducted by the lander
    Humanoid *abductedHumanoid;
    //sf::Vector2f velocity; // Add this member variable to store the velocity
};