#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Circle Origin Example");

    sf::RectangleShape rect(sf::Vector2f(200.f, 100.f));

    // rect.setOrigin({0, 0});         // top-left corner is origin (default)
    // rect.setPosition({400, 300}); // top-left corner is at (400, 300)

    rect.setOrigin({100, 50});    // center is now the origin
    rect.setPosition({400, 300}); // center is placed at (400, 300)

    std::cout << rect.getOrigin().x << std::endl;
    std::cout << rect.getOrigin().y << std::endl;
    std::cout << rect.getPosition().x << std::endl;
    std::cout << rect.getPosition().y << std::endl;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // when close button is clicked
            // or when escape button is pressed
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}
