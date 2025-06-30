#include <SFML/Graphics.hpp>

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

    // check all the window's events that were triggered since the last iteration of the loop
    // / handle events
    const auto onClose = [&window](const sf::Event::Closed &)
    {
        window.close();
    };

    const auto onKeyPressed = [&window](const sf::Event::KeyPressed &keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
            window.close();
    };

    while (window.isOpen())
    {
        window.handleEvents(onClose, onKeyPressed);
    }

    return 0;
}