#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

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
    std::vector<sf::Vector2f> ballSpeed;
    float circleRadius = 50.f;

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
                    if (mouseButtonPressed->position.x > 0 && mouseButtonPressed->position.x < SCR_WIDTH - (2 * circleRadius) && mouseButtonPressed->position.y > 0 && mouseButtonPressed->position.y < SCR_HEIGHT - (2 * circleRadius))
                    {
                        sf::CircleShape ball(circleRadius);
                        float xpos = static_cast<float>(mouseButtonPressed->position.x);
                        float ypos = static_cast<float>(mouseButtonPressed->position.y);
                        ball.setPosition({xpos, ypos});
                        std::random_device rd;
                        std::mt19937 rng(rd());
                        float red = std::uniform_real_distribution(0.f, 255.f)(rng);
                        float green = std::uniform_real_distribution(0.f, 255.f)(rng);
                        float blue = std::uniform_real_distribution(0.f, 255.f)(rng);
                        ball.setFillColor(sf::Color(red, green, blue));
                        balls.push_back(ball);
                        float xSpeed = std::uniform_real_distribution(-10.f, 10.f)(rng);
                        float ySpeed = std::uniform_real_distribution(-10.f, 10.f)(rng);
                        ballSpeed.push_back({xSpeed, ySpeed});

                        std::cout << "ball " << balls.size() << ", " << " xSpeed: " << xSpeed << ", ySpeed: " << ySpeed << std::endl;
                    }
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < balls.size(); i++)
        {
            window.draw(balls[i]);

            float x = balls[i].getPosition().x + ballSpeed[i].x;
            float y = balls[i].getPosition().y + ballSpeed[i].y;

            if (x <= 0 || x >= SCR_WIDTH - (2 * circleRadius))
            {
                // ballSpeed[i].x = -ballSpeed[i].x;
                ballSpeed[i].x *= -1;
                x += ballSpeed[i].x;
            }

            if (y <= 0 || y >= SCR_HEIGHT - (2 * circleRadius))
            {
                // ballSpeed[i].y = -ballSpeed[i].y;
                ballSpeed[i].y *= -1;
                y += ballSpeed[i].y;
            }

            balls[i].setPosition({x, y});
        }

        // end the current frame
        window.display();
    }

    return 0;
}
