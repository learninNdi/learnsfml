#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

float e = 0.5;              // coefficient of restitution
float g = 980;              // pixel/s^2
float groundFriction = 0.8; // friction factor on bounce
float xSpeed = 300.f;       // initial horizontal speed
float ySpeed = 0;
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
    ball.setPosition({640, 10});
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
        float x = ball.getPosition().x;
        float y = ball.getPosition().y;

        // apply gravity
        ySpeed += g * deltaTime;
        y += ySpeed * deltaTime;

        // apply horizontal motion
        x += xSpeed * deltaTime;

        if (y > groundY)
        {
            y = groundY;
            ySpeed *= -e;

            // apply friction to horizontal speed
            xSpeed *= groundFriction;

            // stop tiny bounces
            if (std::abs(ySpeed) < 10)
                ySpeed = 0;

            if (std::abs(xSpeed) < 10)
                xSpeed = 0;
        }

        // bounce off left/right walls
        if (x <= 0 || x > SCR_WIDTH - (2 * ballRadius))
        {
            x = std::clamp(x, 0.f, SCR_WIDTH - (2 * ballRadius));
            xSpeed *= -e; // reflect with some loss
        }

        ball.setPosition({x, y});

        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(ball);

        // end the current frame
        window.display();
    }

    return 0;
}
