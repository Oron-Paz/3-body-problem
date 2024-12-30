#include "Slider.h"
#include <sstream>
#include <iomanip>

Slider::Slider(const sf::Font& font, const std::string& labelText, float* value,
               float min, float max, const sf::Vector2f& pos)
    : label(font, "")           // Initialize with font
    , valueText(font, "")       // Initialize with font
    , minValue(min)
    , maxValue(max)
    , valuePtr(value)
    , isDragging(false)
    , position(pos)
{    
    // Setup bar
    bar.setSize(sf::Vector2f(200.f, 10.f));
    bar.setPosition(position);
    bar.setFillColor(sf::Color(100, 100, 100));

    // Setup handle
    handle.setSize(sf::Vector2f(20.f, 20.f));
    float handleX = position.x + ((*value - minValue) / (maxValue - minValue)) * 180.f;
    handle.setPosition(sf::Vector2f(handleX, position.y - 5.f));
    handle.setFillColor(sf::Color::White);

    // Setup label
    label.setString(labelText);
    label.setCharacterSize(16);
    label.setPosition(sf::Vector2f(position.x, position.y - 25.f));
    label.setFillColor(sf::Color::White);

    // Setup value text
    valueText.setCharacterSize(16);
    valueText.setPosition(sf::Vector2f(position.x + 220.f, position.y - 5.f));
    valueText.setFillColor(sf::Color::White);

    // Set initial value text
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << *valuePtr;
    valueText.setString(ss.str());
}

void Slider::update(const sf::Vector2f& mousePos, bool mousePressed) {
    sf::FloatRect handleBounds = handle.getGlobalBounds();
    
    if (mousePressed && handleBounds.contains(mousePos)) {
        isDragging = true;
    }
    
    if (!mousePressed) {
        isDragging = false;
    }
    
    if (isDragging) {
        float newX = mousePos.x;
        newX = std::max(position.x, std::min(position.x + 180.f, newX));
        handle.setPosition(sf::Vector2f(newX, position.y - 5.f));
        
        // Update the linked value
        float percent = (newX - position.x) / 180.f;
        *valuePtr = minValue + percent * (maxValue - minValue);
        
        // Update value text
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << *valuePtr;
        valueText.setString(ss.str());
    }
}

void Slider::draw(sf::RenderWindow& window) {
    window.draw(bar);
    window.draw(handle);
    window.draw(label);
    window.draw(valueText);
}
