#include <SFML/Graphics.hpp>

#include <iostream>
#include <algorithm>
#include <random>

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

float e = 0.5;              // coefficient of restitution
float g = 980;              // pixel/s^2
float groundFriction = 0.8; // friction factor on bounce
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
    std::vector<sf::CircleShape> balls;
    std::vector<sf::Vector2f> velocity;
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
            else if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    if (mouseButtonPressed->position.x > 0 && mouseButtonPressed->position.x < SCR_WIDTH - (2 * ballRadius) && mouseButtonPressed->position.y > 0 && mouseButtonPressed->position.y < SCR_HEIGHT - (2 * ballRadius))
                    {
                        float xpos = static_cast<float>(mouseButtonPressed->position.x);
                        float ypos = static_cast<float>(mouseButtonPressed->position.y);
                        sf::CircleShape ball(ballRadius);
                        ball.setPosition({xpos, ypos});
                        std::random_device rd;
                        std::mt19937 rng(rd());
                        float red = std::uniform_real_distribution(0.f, 255.f)(rng);
                        float green = std::uniform_real_distribution(0.f, 255.f)(rng);
                        float blue = std::uniform_real_distribution(0.f, 255.f)(rng);
                        ball.setFillColor(sf::Color(red, green, blue));
                        balls.push_back(ball);

                        float xSpeed;
                        xSpeed = std::uniform_real_distribution(-300.f, 300.f)(rng);

                        velocity.push_back({xSpeed, 0});
                    }
                }
            }
        }

        deltaTime = clock.restart().asSeconds();

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < balls.size(); i++)
        {
            float x = balls[i].getPosition().x;
            float y = balls[i].getPosition().y;

            // apply gravity
            velocity[i].y += g * deltaTime;
            y += velocity[i].y * deltaTime;

            // apply horizontal motion
            x += velocity[i].x * deltaTime;

            if (y > groundY)
            {
                y = groundY;
                velocity[i].y *= -e;

                // apply friction to horizontal speed
                velocity[i].x *= groundFriction;

                // stop tiny bounces
                if (std::abs(velocity[i].y) < 10)
                    velocity[i].y = 0;

                if (std::abs(velocity[i].x) < 10)
                    velocity[i].x = 0;
            }

            // bounce off left/right walls
            if (x <= 0 || x > SCR_WIDTH - (2 * ballRadius))
            {
                x = std::clamp(x, 0.f, SCR_WIDTH - (2 * ballRadius));
                velocity[i].x *= -e; // reflect with some loss
            }

            balls[i].setPosition({x, y});

            window.draw(balls[i]);
        }

        // end the current frame
        window.display();
    }

    return 0;
}
