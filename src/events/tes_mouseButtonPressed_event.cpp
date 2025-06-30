#include <SFML/Graphics.hpp>

#include <iostream>

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

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        // / handle events
        while (const std::optional event = window.pollEvent())
        {
            // when close button is clicked
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }

            if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                switch (mouseButtonPressed->button)
                {
                case sf::Mouse::Button::Left:
                    std::cout << "mouse left button pressed" << std::endl;
                    break;
                case sf::Mouse::Button::Middle:
                    std::cout << "mouse middle button pressed" << std::endl;
                    break;
                case sf::Mouse::Button::Right:
                    std::cout << "mouse right button pressed" << std::endl;
                    break;
                }

                std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
            }

            if (const auto *mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                switch (mouseButtonReleased->button)
                {
                case sf::Mouse::Button::Left:
                    std::cout << "mouse left button released" << std::endl;
                    break;
                case sf::Mouse::Button::Middle:
                    std::cout << "mouse middle button released" << std::endl;
                    break;
                case sf::Mouse::Button::Right:
                    std::cout << "mouse right button released" << std::endl;
                    break;
                }

                std::cout << "mouse x: " << mouseButtonReleased->position.x << std::endl;
                std::cout << "mouse y: " << mouseButtonReleased->position.y << std::endl;
            }
        }
    }

    return 0;
}