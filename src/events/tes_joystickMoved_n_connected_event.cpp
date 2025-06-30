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

            if (const auto *joystickMoved = event->getIf<sf::Event::JoystickMoved>())
            {
                if (joystickMoved->axis == sf::Joystick::Axis::X)
                {
                    std::cout << "X axis moved" << std::endl;
                    std::cout << "joystick id: " << joystickMoved->joystickId << std::endl;
                }

                if (joystickMoved->axis == sf::Joystick::Axis::Y)
                {
                    std::cout << "Y axis moved" << std::endl;
                    std::cout << "joystick id: " << joystickMoved->joystickId << std::endl;
                }

                std::cout << "new position: " << joystickMoved->position << std::endl;
            }

            if (event->getIf<sf::Event::JoystickConnected>())
                std::cout << "joystick connected" << std::endl;

            if (event->getIf<sf::Event::JoystickDisconnected>())
                std::cout << "joystick disconnected" << std::endl;
        }
    }

    return 0;
}