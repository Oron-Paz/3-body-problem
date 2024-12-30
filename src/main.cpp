#include <SFML/Graphics.hpp>
#include "Body.h"
#include "Slider.h"

int main()
{
    // create the main window
    sf::RenderWindow window(sf::VideoMode({800, 800}), "SFML window");
    window.setFramerateLimit(60);
    
    // Load font
    sf::Font font;
    if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {  // Standard Mac font path
    // Try backup system font if Arial isn't found
         if (!font.openFromFile("/System/Library/Fonts/Helvetica.ttc")) {
             return -1;
         }
    } 

    Body body1(300.0f, 250.0f, 0.0f, 0.0f, 300.0f, 10.0f, sf::Color::Red);
    Body body2(400.0f, 350.0f, 0.0f, 0.0f, 300.0f, 10.0f, sf::Color::Blue);
    Body body3(500.0f, 300.0f, 0.0f, 0.0f, 300.0f, 10.0f, sf::Color::Green);
    
    // Initialize G value
    float G = 1500.0f;
    
    // Create sliders
    std::vector<Slider> sliders;
    sliders.emplace_back(font, "G Constant", &G, 0.0f, 5000.0f, sf::Vector2f(50, 600));
    sliders.emplace_back(font, "Red Mass", &body1.mass, 50.0f, 1000.0f, sf::Vector2f(50, 700));
    sliders.emplace_back(font, "Blue Mass", &body2.mass, 50.0f, 1000.0f, sf::Vector2f(50, 750));
    sliders.emplace_back(font, "Green Mass", &body3.mass, 50.0f, 1000.0f, sf::Vector2f(50, 650));

    const float delta_time = 0.016f;
    
    // start the game loop
    while (window.isOpen())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        // process events
        while (const std::optional event = window.pollEvent())
        {
            // close window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Update sliders
        for (auto& slider : sliders) {
            slider.update(sf::Vector2f(mousePos), mousePressed);
        }

        // Update G constant
        body1.setG(G);
        body2.setG(G);
        body3.setG(G);

        // Calculate gravitational forces
        body1.applyForces(body2);
        body1.applyForces(body3);
        body2.applyForces(body1);
        body2.applyForces(body3);
        body3.applyForces(body1);
        body3.applyForces(body2);

        body1.updatePosition(delta_time);
        body2.updatePosition(delta_time);
        body3.updatePosition(delta_time);

        // clear screen
        window.clear(sf::Color::Black);

        // draw bodies
        body1.draw(window);
        body2.draw(window);
        body3.draw(window);

        // draw sliders
        for (auto& slider : sliders) {
            slider.draw(window);
        }

        // update the window
        window.display();
    }
    
    return 0;
}
