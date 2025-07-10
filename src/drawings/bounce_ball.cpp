#include <SFML/Graphics.hpp>

#include <iostream>

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

float e = 0.5; // coefficient of restitution
float g = 980; // pixel/s^2
float groundFriction = 0.5;
float ballRadius = 25;
float groundY = SCR_HEIGHT - (2 * ballRadius);

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

    // BallSystem balls;
    sf::CircleShape ball(ballRadius);
    float yPos = 10;
    ball.setPosition({640, yPos});
    float velocity = 0;
    float deltaTime;

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

        deltaTime = clock.restart().asSeconds();
        float y = ball.getPosition().y;

        // apply gravity
        velocity += g * deltaTime;
        y += velocity * deltaTime;

        if (y > groundY)
        {
            y = groundY;
            velocity *= -e;

            // stop tiny bounces
            if (std::abs(velocity) < (2 * ballRadius))
                velocity = 0;
        }

        ball.setPosition({640, y});

        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(ball);

        // end the current frame
        window.display();
    }

    return 0;
}
