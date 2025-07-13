#include <SFML/Graphics.hpp>
#include <cmath>

const float PI = 3.14159265f;

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Orbiting Ball");
    window.setFramerateLimit(60);

    // Orbit center (e.g., the sun)
    sf::CircleShape center(20);
    center.setFillColor(sf::Color::Yellow);
    // center.setOrigin({20, 20});   // center the origin
    center.setPosition({50, 50}); // screen center

    // Orbiting ball (e.g., a planet)
    sf::CircleShape orbiter(10);
    orbiter.setFillColor(sf::Color::Cyan);
    orbiter.setOrigin({10, 10}); // center the origin

    float angle = 0.0f;        // current angle in radians
    float radius = 150.0f;     // orbit radius
    float angularSpeed = 1.0f; // radians per second

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // when close button is clicked
            // or when escape button is pressed
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        float dt = clock.restart().asSeconds();

        // Update angle
        angle += angularSpeed * dt;
        if (angle > 2 * PI)
            angle -= 2 * PI;

        // Compute new position using sine & cosine
        float x = center.getPosition().x + radius * std::cos(angle);
        float y = center.getPosition().y + radius * std::sin(angle);
        orbiter.setPosition({x, y});

        // Draw
        window.clear(sf::Color::Black);
        window.draw(center);
        // window.draw(orbiter);
        window.display();
    }

    return 0;
}
