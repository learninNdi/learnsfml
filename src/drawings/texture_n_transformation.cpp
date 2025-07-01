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

    // load texture
    int texWidth = 128;
    int texHeight = 128;
    sf::Texture texture("../assets/img/tex1.jpg", false, sf::IntRect({128, 128}, {texWidth, texHeight}));

    texture.setSmooth(true);
    // texture.setRepeated(true);

    // create sprite
    sf::Sprite sprite(texture);
    
    // set sprite color
    sprite.setColor(sf::Color(0, 255, 0));

    // // set sprite position
    // sprite.setPosition({10.f, 50.f});       // absolute position
    // sprite.move({50.f, 10.f});              // offset relative to the current position

    // // rotation
    // sprite.setRotation(sf::degrees(-45));   // absolute angle
    // sprite.rotate(sf::degrees(10));         // offset relative to the current angle

    // // scale
    // sprite.setScale({0.5f, 2.f});           // absolute scale factor
    // sprite.scale({1.5f, 3.f});              // offset relative to the current scale

    // // set origin
    // sprite.setOrigin({75.f, 75.f});

    float xPos = 0.f;
    // float xPos = SCR_WIDTH - texWidth;
    float yPos = 0.f;
    // float yPos = SCR_HEIGHT - texHeight;
    sprite.setPosition({xPos, yPos});

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
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here
        window.draw(sprite);

        if (sprite.getPosition().x >= 0 && sprite.getPosition().x < SCR_WIDTH - texWidth && sprite.getPosition().y == 0)
        {
            if (sprite.getPosition().x < SCR_WIDTH - texWidth) sprite.move({1, 0});
            else
            {
                xPos = SCR_WIDTH - texWidth;
                sprite.setPosition({xPos, yPos});
            }
        } else if (sprite.getPosition().x == SCR_WIDTH - texWidth && sprite.getPosition().y >= 0 && sprite.getPosition().y < SCR_HEIGHT - texHeight)
        {
            if (sprite.getPosition().y < SCR_HEIGHT - texHeight) sprite.move({0, 1});
            else
            {
                yPos = SCR_HEIGHT - texHeight;
                sprite.setPosition({xPos, yPos});
            }
        } else if (sprite.getPosition().x > 0 && sprite.getPosition().x <= SCR_WIDTH - texWidth && sprite.getPosition().y == SCR_HEIGHT - texHeight)
        {
            if (sprite.getPosition().x > 0) sprite.move({-1, 0});
            else
            {
                xPos = 0.f;
                sprite.setPosition({xPos, yPos});
            }
        } else if (sprite.getPosition().x == 0 && sprite.getPosition().y > 0 && sprite.getPosition().y <= SCR_HEIGHT - texHeight)
        {
            if (sprite.getPosition().y > 0) sprite.move({0, -1});
            else
            {
                yPos = 0.f;
                sprite.setPosition({xPos, yPos});
            }
        }

        // end the current frame
        window.display();

    }

    return 0;
}