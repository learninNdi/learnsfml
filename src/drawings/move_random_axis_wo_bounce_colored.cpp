#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

double Pi = 3.1415926535897932384626433832795;
double epsilon = 1e-9;

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
    std::vector<float> ballDir;
    float circleRadius = 10.f;
    float speed = 5;

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
                    std::random_device rd;
                    std::mt19937 rng(rd());
                    float red = std::uniform_real_distribution(0.f, 255.f)(rng);
                    float green = std::uniform_real_distribution(0.f, 255.f)(rng);
                    float blue = std::uniform_real_distribution(0.f, 255.f)(rng);
                    ball.setFillColor(sf::Color(red, green, blue));
                    balls.push_back(ball);
                    ballDir.push_back(std::uniform_real_distribution(0.f, 360.f)(rng));
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < balls.size(); i++)
        {
            window.draw(balls[i]);

            float nextXPos = cos(ballDir[i] * Pi / 180);
            float nextYPos = sin(ballDir[i] * Pi / 180);

            if (nextXPos > 0 && nextXPos < epsilon)
                nextXPos = 0;
            if (nextYPos > 0 && nextYPos < epsilon)
                nextYPos = 0;

            balls[i].move({nextXPos * speed, nextYPos * speed});

            if (balls[i].getPosition().x > SCR_WIDTH - (2 * circleRadius) || balls[i].getPosition().y > SCR_HEIGHT - (2 * circleRadius) || balls[i].getPosition().x < 0 || balls[i].getPosition().y < 0)
            {
                balls.erase(balls.begin() + i);
                ballDir.erase(ballDir.begin() + i);
            }
        }

        // end the current frame
        window.display();
    }

    return 0;
}
