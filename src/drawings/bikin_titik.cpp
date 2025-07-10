#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 1024;

std::vector<sf::RectangleShape> snake;
float snakePartSize = 20;

int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode({SCR_WIDTH, SCR_HEIGHT}), "Game Uler");
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

    std::random_device rd;
    std::mt19937 rng(rd());

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
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                {
                    float xPos = std::uniform_real_distribution(0.f, SCR_WIDTH - snakePartSize)(rng);
                    float yPos = std::uniform_real_distribution(0.f, SCR_WIDTH - snakePartSize)(rng);
                    sf::RectangleShape snakePart({20, 20});
                    snakePart.setPosition({xPos, yPos});
                    snake.push_back(snakePart);
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                {
                    if (snake.size())
                        snake.pop_back();
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < snake.size(); i++)
            window.draw(snake[i]);

        // end the current frame
        window.display();
    }

    return 0;
}
