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

    int texWidth = 128;
    int texHeight = 128;
    sf::Texture texture("../assets/img/tex1.jpg", false, sf::IntRect({128, 128}, {texWidth, texHeight}));

    texture.setSmooth(true);

    sf::CircleShape shape(50.f);
    // shape.setFillColor(sf::Color(100, 250, 50));

    // // set a 10-pixel wide orange outline
    // shape.setOutlineThickness(-10.f);
    // shape.setOutlineColor(sf::Color(250, 150, 100));

    // map a 100x100 textured rectangle to the shape
    shape.setTexture(&texture);
    shape.setTextureRect(sf::IntRect({10, 10}, {100, 100}));

    sf::RectangleShape rectangle({120.f, 50.f});
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition({780.f, 0});

    sf::CircleShape triangle(80.f, 3);
    triangle.setFillColor(sf::Color::Blue);
    triangle.setPosition({0, 400});

    sf::CircleShape square(80.f, 4);
    square.setFillColor(sf::Color::Magenta);
    square.setPosition({200, 400});

    sf::CircleShape octagon(80.f, 8);
    octagon.setFillColor(sf::Color::Cyan);
    octagon.setPosition({400, 400});

    sf::ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0, {600, 20});
    convex.setPoint(1, {600, 40});
    convex.setPoint(2, {700, 100});
    convex.setPoint(3, {750, 200});
    convex.setPoint(4, {750, 100});

    // line with thickness
    sf::RectangleShape line1({150, 5});
    line1.rotate(sf::degrees(45));
    line1.setPosition({0, 100});

    // line without thickness
    std::array line =
        {
            sf::Vertex{sf::Vector2f(10.f, 10.f)},
            sf::Vertex{sf::Vector2f(150.f, 150.f)},
        };

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
        window.draw(shape);
        window.draw(rectangle);
        window.draw(triangle);
        window.draw(square);
        window.draw(octagon);
        window.draw(convex);
        window.draw(line1);
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);

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
