#include <SFML/Graphics.hpp>

unsigned int SCR_WIDTH = 640;
unsigned int SCR_HEIGHT = 480;

char *imagePath = "../assets/img/tex1.jpg";

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode({SCR_WIDTH, SCR_HEIGHT}), "First Window");

    sf::RectangleShape rectangle({128, 128});
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition({320, 240});
    rectangle.setOrigin({rectangle.getSize().x / 2, rectangle.getSize().y / 2});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        // draw here
        window.draw(rectangle);

        window.display();
    }

    return 0;
}
