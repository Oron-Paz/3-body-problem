#pragma once
#include <SFML/Graphics.hpp>

class Body {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float radius;
    sf::CircleShape shape;
    sf::Color color;
    // Add trail storage
    std::vector<sf::Vector2f> trail;
    static const size_t TRAIL_LENGTH = 50;
    static float G;

public:
    Body(float x, float y, float vx, float vy, float m, float r, sf::Color c);
    void draw(sf::RenderWindow& window);
    void updatePosition(float delta_time);
    void applyForces(Body& other);
    float getMass() const;
    sf::Vector2f getPosition() const;
    float getRadius() const;
    void drawTrail(sf::RenderWindow& window);
    static void setG(float newG) { G = newG; }
    float mass;
};
