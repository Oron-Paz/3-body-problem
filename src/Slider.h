// Slider.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Slider {
private:
    sf::RectangleShape bar;
    sf::RectangleShape handle;
    sf::Text label;
    sf::Text valueText;
    float minValue;
    float maxValue;
    float* valuePtr;
    bool isDragging;
    sf::Vector2f position;

public:
    Slider(const sf::Font& font, const std::string& labelText, float* value, 
           float min, float max, const sf::Vector2f& pos);
    void update(const sf::Vector2f& mousePos, bool mousePressed);
    void draw(sf::RenderWindow& window);
};
