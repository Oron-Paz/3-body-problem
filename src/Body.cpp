#include "Body.h"
#include <cmath>
#include <SFML/Graphics.hpp>

float Body::G = 1500.0f;  // Initialize the static member

Body::Body(float x, float y, float vx, float vy, float m, float r, sf::Color c) 
    : position(x, y), 
      velocity(vx, vy), 
      acceleration(0.0f, 0.0f),
      mass(m), 
      radius(r), 
      color(c) {
    shape.setRadius(radius);
    shape.setFillColor(c);
    shape.setOrigin(sf::Vector2f(radius, radius));
    shape.setPosition(position);
    // Initialize first trail position
    trail.push_back(position);
}


void Body::updatePosition(float delta_time) {
    // Store position in trail before updating
    if (trail.size() >= TRAIL_LENGTH) {
        trail.erase(trail.begin());
    }
    trail.push_back(position);

    velocity += acceleration * delta_time;
    position += velocity * delta_time;
    
    // Fixed boundary checking with absolute limits
    if (position.y >= 600.0f - radius) {
        position.y = 600.0f - radius;
        velocity.y = -velocity.y * 0.95f;
    }
    if (position.y <= radius) {
        position.y = radius;
        velocity.y = -velocity.y * 0.95f;
    }
    if (position.x >= 800.0f - radius) {
        position.x = 800.0f - radius;
        velocity.x = -velocity.x * 0.95f;
    }
    if (position.x <= radius) {
        position.x = radius;
        velocity.x = -velocity.x * 0.95f;
    }
    
    shape.setPosition(position);
    acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Body::applyForces(Body& other) {
    
    sf::Vector2f r = other.getPosition() - position;
    float distance = sqrt(r.x * r.x + r.y * r.y);
    
    if (distance < radius + other.getRadius() || distance < 1.0f) return;
    
    float force = (G * (mass * other.getMass())) / (distance * distance);
    sf::Vector2f force_vector = r * (force/distance);
    
    acceleration += force_vector / mass;
}

float Body::getMass() const {
    return mass;
}

sf::Vector2f Body::getPosition() const {
    return position;
}

float Body::getRadius() const {
    return radius;
}

void Body::draw(sf::RenderWindow& window) {
    drawTrail(window);  // Draw trail first (behind the body)
    window.draw(shape);
}

void Body::drawTrail(sf::RenderWindow& window) {
    for (size_t i = 0; i < trail.size(); i++) {
        sf::CircleShape trailDot(2.0f);
        trailDot.setPosition(trail[i]);
        // Fix setOrigin to use Vector2f
        trailDot.setOrigin(sf::Vector2f(1.0f, 1.0f));
        
        // Fix Uint8 to sf::Uint8
        sf::Color trailColor = color;
        trailColor.a = static_cast<uint8_t>(255 * (static_cast<float>(i) / trail.size()));
        trailDot.setFillColor(trailColor);
        
        window.draw(trailDot);
    }
}
