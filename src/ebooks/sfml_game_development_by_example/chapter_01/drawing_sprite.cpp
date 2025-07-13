#include <SFML/Graphics.hpp>

#include <iostream>

unsigned int SCR_WIDTH = 640;
unsigned int SCR_HEIGHT = 480;

// char *mushroomImagePath = "../assets/img/Mushroom.png";

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode({SCR_WIDTH, SCR_HEIGHT}), "First Window");

    sf::Texture mushroomTexture;
    if (!mushroomTexture.loadFromFile("../assets/img/Mushroom.png"))
        std::cout << "error loading texture file" << std::endl;

    sf::Sprite mushroom(mushroomTexture);

    mushroom.setColor(sf::Color(255, 127, 0, 255));

    sf::Vector2u size = mushroomTexture.getSize();
    mushroom.setOrigin({(float)size.x / 2, (float)size.y / 2});
    sf::Vector2f increment(0.1f, 0.1f);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        if ((mushroom.getPosition().x + (size.x / 2) > SCR_WIDTH && increment.x > 0) || (mushroom.getPosition().x - (size.x / 2) < 0 && increment.x < 0))
            // reverse the direction on X axis
            increment.x *= -1;

        if ((mushroom.getPosition().y + (size.y / 2) > SCR_HEIGHT && increment.y > 0) || (mushroom.getPosition().y - (size.y / 2) < 0 && increment.y < 0))
            // reverse the direction on Y axis
            increment.y *= -1;

        mushroom.setPosition(mushroom.getPosition() + increment);

        window.clear(sf::Color(16, 16, 16, 255)); // dark gray

        // draw here
        // window.draw(rectangle);
        window.draw(mushroom);

        window.display();
    }

    return 0;
}
