#include <SFML/Graphics.hpp>

int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");

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
        }
    }

    return 0;
}