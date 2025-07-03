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

    // // create a new vertex
    // sf::Vertex vertex;

    // // set its position
    // vertex.position = sf::Vector2f(10.f, 50.f);

    // // set its color
    // vertex.color = sf::Color::Red;

    // // set its texture coordinates
    // vertex.texCoords = sf::Vector2f(100.f, 100.f);

    // // using aggregate initialization
    // sf::Vertex vertex{{10.f, 50.f}, sf::Color::Red, {100.f, 100.f}};

    // create an array of 3 vertices that define a triangle primitive
    sf::VertexArray triangle(sf::PrimitiveType::Triangles, 3);

    // define the position of the triangle's points
    triangle[0].position = sf::Vector2f(10.f, 10.f);
    triangle[1].position = sf::Vector2f(100.f, 10.f);
    triangle[2].position = sf::Vector2f(100.f, 100.f);

    // define the color of the triangle's points
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    // // set a 10-pixel wide orange outline
    // shape.setOutlineThickness(-10.f);
    // shape.setOutlineColor(sf::Color(250, 150, 100));

    // map a 100x100 textured rectangle to the shape
    // shape.setTexture(&texture);
    // shape.setTextureRect(sf::IntRect({10, 10}, {100, 100}));

    // // set text style
    // text.setStyle(sf::Text::Bold | sf::Text::Underlined);

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

    // float xPos = 0.f;
    // // float xPos = SCR_WIDTH - texWidth;
    // float yPos = 0.f;
    // // float yPos = SCR_HEIGHT - texHeight;
    // text.setPosition({xPos, yPos});

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
        window.draw(triangle);

        // if (text.getPosition().x >= 0 && text.getPosition().x < SCR_WIDTH - 128 && text.getPosition().y == 0)
        // {
        //     if (text.getPosition().x < SCR_WIDTH - 128)
        //         text.move({1.5, 0});
        //     else
        //     {
        //         xPos = SCR_WIDTH - 128;
        //         text.setPosition({xPos, yPos});
        //     }
        // }
        // else if (text.getPosition().x == SCR_WIDTH - 128 && text.getPosition().y >= 0 && text.getPosition().y < SCR_HEIGHT - charSize)
        // {
        //     if (text.getPosition().y < SCR_HEIGHT - charSize)
        //         text.move({0, 1.5});
        //     else
        //     {
        //         yPos = SCR_HEIGHT - charSize;
        //         text.setPosition({xPos, yPos});
        //     }
        // }
        // else if (text.getPosition().x > 0 && text.getPosition().x <= SCR_WIDTH - 128 && text.getPosition().y == SCR_HEIGHT - charSize)
        // {
        //     if (text.getPosition().x > 0)
        //         text.move({-1.5, 0});
        //     else
        //     {
        //         xPos = 0.f;
        //         text.setPosition({xPos, yPos});
        //     }
        // }
        // else if (text.getPosition().x == 0 && text.getPosition().y > 0 && text.getPosition().y <= SCR_HEIGHT - charSize)
        // {
        //     if (text.getPosition().y > 0)
        //         text.move({0, -1.5});
        //     else
        //     {
        //         yPos = 0.f;
        //         text.setPosition({xPos, yPos});
        //     }
        // }

        // end the current frame
        window.display();
    }

    return 0;
}
