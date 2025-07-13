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
    sun.setFillColor(sf::Color::Yellow);
    sun.setOrigin({sunRadius, sunRadius});

    float earthRadius = 10;
    sf::CircleShape earth(earthRadius);
    earth.setFillColor(sf::Color::Cyan);
    earth.setOrigin({earthRadius, earthRadius});

    // orbit parameters
    float a = 200;                       // semi-major axis
    float e = 0.5f;                      // eccentricity (0 = circle, < 1 = ellipse)
    float b = a * std::sqrtf(1 - e * e); // semi-minor axis
    float angle = 0.f;                   // angle in radians
    float angularSpeed = 0.5f;           // radians per second

    // position the sun offset due to ellipse center
    sf::Vector2f orbitCenter({(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 2});
    sf::Vector2f sunPos = orbitCenter;
    sunPos.x -= e * a; // shift sun to the left focus of ellipse
    sun.setPosition(sunPos);

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

        angle -= angularSpeed * dt;
        if (angle < 2 * PI)
            angle += 2 * PI;

        // earth position along ellipse
        float x = a * std::cosf(angle);
        float y = b * std::sinf(angle);

        earth.setPosition({orbitCenter.x + x, orbitCenter.y + y});

        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(sun);
        window.draw(earth);

        // end the current frame
        window.display();
    }

    return 0;
}
