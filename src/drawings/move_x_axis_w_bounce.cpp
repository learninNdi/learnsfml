#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

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
    std::vector<int> ballDir;
    float circleRadius = 10.f;

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
                    sf::CircleShape ball(circleRadius);
                    float xpos = static_cast<float>(mouseButtonPressed->position.x);
                    float ypos = static_cast<float>(mouseButtonPressed->position.y);
                    ball.setPosition({xpos, ypos});
                    balls.push_back(ball);
                    std::random_device rd;
                    std::mt19937 rng(rd());
                    float dir = std::uniform_real_distribution(0.f, 100.f)(rng);
                    ballDir.push_back(dir >= 50 ? 1 : 0);
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < balls.size(); i++)
        {
            window.draw(balls[i]);

            if (ballDir[i])
                balls[i].move({3, 0});
            else
                balls[i].move({-3, 0});

            if (balls[i].getPosition().x >= SCR_WIDTH - (2 * circleRadius) && ballDir[i])
                ballDir[i] = 0;
            else if (balls[i].getPosition().x <= 0 && !ballDir[i])
                ballDir[i] = 1;
        }

        // end the current frame
        window.display();
    }

    return 0;
}
