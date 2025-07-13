#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

const float PI = 3.14159265f;

int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode({SCR_WIDTH, SCR_HEIGHT}), "Learn SFML");
    window.setPosition({
        static_cast<int>((sf::VideoMode::getDesktopMode().size.x - SCR_WIDTH) / 2),
        static_cast<int>((sf::VideoMode::getDesktopMode().size.y - SCR_WIDTH) / 2),
    });

    // optional: set verticalsync
    // window.setVerticalSyncEnabled(true);

    // optional: set frameratelimit
    window.setFramerateLimit(60);

    // note: never use both setverticalsync and setframelimit at the same time!
    // they would badly mix and make things worse

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // BallSystem balls;
    float sunRadius = 20;
    sf::CircleShape sun(sunRadius);
    float centerX = SCR_WIDTH / 2;
    float centerY = SCR_HEIGHT / 2;
    sun.setFillColor(sf::Color::Yellow);
    sun.setOrigin({sunRadius, sunRadius});
    sun.setPosition({centerX, centerY});
    // circle1.setOrigin({centerX, centerY});

    float earthRadius = 10;
    sf::CircleShape earth(earthRadius);
    earth.setFillColor(sf::Color::Cyan);
    earth.setOrigin({earthRadius, earthRadius});

    float radius = 100;
    float angle = 0.f;
    float angularSpeed = 0.5f; // radians per second

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        // / handle events
        while (const std::optional event = window.pollEvent())
        {
            // when close button is clicked
            // or when escape button is pressed
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        float dt = clock.restart().asSeconds();

        angle += angularSpeed * dt;
        if (angle > 2 * PI)
            angle -= 2 * PI;

        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);

        earth.setPosition({x, y});

        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(sun);
        window.draw(earth);

        // end the current frame
        window.display();
    }

    return 0;
}
