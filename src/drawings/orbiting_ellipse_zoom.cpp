#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

const float PI = 3.14159265f;

struct Planet
{
    sf::CircleShape shape;
    float radius;
    float semiMajorXAxis;
    float eccentricity;
    float velocity;
    sf::Color color;
    float angle;

    Planet(float r, float a, float e, float planetSpeed, float planetAngle, sf::Color planetColor)
    {
        radius = r;
        semiMajorXAxis = a;
        eccentricity = e;
        velocity = planetSpeed;
        color = planetColor;
        angle = planetAngle;

        shape.setRadius(r);
        shape.setOrigin({r, r});
        shape.setFillColor(color);
    }

    void setPosition(sf::Vector2f pos)
    {
        shape.setPosition(pos);
    }
};

std::random_device rd;
std::mt19937 rng(rd());
float red = std::uniform_real_distribution(0.f, 255.f)(rng);

std::vector<Planet> planets = {
    // Planet(0.00002439, 0.39, 0.205, 47.9f, sf::Color(26, 26, 26)),    // mercury
    // Planet(0.00006051, 0.72, 0.006, 35.0f, sf::Color(230, 230, 230)), // venus
    // Planet(0.00006371, 1.f, 0.016, 29.8f, sf::Color(47, 106, 105)),   // earth
    // Planet(0.00003389, 1.52, 0.093, 24.1f, sf::Color(153, 61, 0)),    // mars
    // Planet(0.00069911, 5.2, 0.048, 13.1f, sf::Color(176, 127, 53)),   // jupyter
    // Planet(0.00058232, 9.54, 0.054, 9.7f, sf::Color(176, 143, 54)),   // saturn
    // Planet(0.00025362, 19.22, 0.047, 6.8f, sf::Color(85, 128, 170)),  // uranus
    // Planet(0.00024622, 30.06, 0.008, 5.4f, sf::Color(54, 104, 150))   // neptune

    Planet(24, 390, 0.205, 0.479f, std::uniform_real_distribution(0.f, 359.f)(rng), sf::Color(26, 26, 26)),        // mercury
    Planet(60, 720, 0.006, 0.35f, std::uniform_real_distribution(0.f, 255.f)(rng), sf::Color(230, 230, 230)),      // venus
    Planet(63.5, 1000, 0.016, 0.298f, std::uniform_real_distribution(0.f, 255.f)(rng), sf::Color(47, 106, 105)),   // earth
    Planet(33.5, 1520, 0.093, 0.241f, std::uniform_real_distribution(0.f, 255.f)(rng), sf::Color(153, 61, 0)),     // mars
    Planet(699, 5200, 0.048, 0.131f, std::uniform_real_distribution(0.f, 255.f)(rng), sf::Color(176, 127, 53)),    // jupyter
    Planet(512, 9540, 0.054, 0.097f, std::uniform_real_distribution(0.f, 255.f)(rng), sf::Color(176, 143, 54)),    // saturn
    Planet(253.5, 19220, 0.047, 0.068f, std::uniform_real_distribution(0.f, 255.f)(rng), sf::Color(85, 128, 170)), // uranus
    Planet(298.5, 300600, 0.008, 0.054f, std::uniform_real_distribution(0.f, 255.f)(rng), sf::Color(54, 104, 150)) // neptune
};

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

    sf::View view(sf::FloatRect({0, 0}, {(float)SCR_WIDTH, (float)SCR_HEIGHT}));

    // note: never use both setverticalsync and setframelimit at the same time!
    // they would badly mix and make things worse

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // // orbit parameters
    // float a = 149.6f;                    // semi-major axis
    // float e = 0.0167f;                   // eccentricity (0 = circle, < 1 = ellipse)
    // float b = a * std::sqrtf(1 - e * e); // semi-minor axis
    // float angle = 0.f;                   // angle in radians
    // float earthSpeed = 0.00107278f;

    // SUN
    float sunRadius = 69.57;
    sf::CircleShape sun(sunRadius);
    sun.setFillColor(sf::Color::Yellow);
    sun.setOrigin({sunRadius, sunRadius});

    // // EARTH
    // float earthRadius = 10;
    // sf::CircleShape earth(earthRadius);
    // earth.setFillColor(sf::Color::Cyan);
    // earth.setOrigin({earthRadius, earthRadius});

    // position the sun offset due to ellipse center
    sf::Vector2f orbitCenter({(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 2});
    sf::Vector2f sunPos = orbitCenter;
    sunPos.x -= planets[2].eccentricity * planets[2].semiMajorXAxis; // shift sun to the left focus of ellipse
    sun.setPosition(sunPos);

    sf::Clock clock;

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

            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::W)
                    view.move({0, -10});
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
                    view.move({0, 10});
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                    view.move({-10, 0});
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                    view.move({10, 0});
            }

            if (const auto *mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                if (mouseWheelScrolled->delta > 0)
                    view.zoom(0.9f);
                else if (mouseWheelScrolled->delta < 0)
                    view.zoom(1.1f);
            }
        }

        float dt = clock.restart().asSeconds();

        for (int i = 0; i < planets.size(); i++)
        {
            if (i == 1)
                planets[i].angle += planets[i].velocity * dt;
            else
                planets[i].angle -= planets[i].velocity * dt;

            if (planets[i].angle < 2 * PI)
                planets[i].angle += 2 * PI;

            // planet position along ellipse
            float x = planets[i].semiMajorXAxis * std::cosf(planets[i].angle);
            float b = planets[i].semiMajorXAxis * std::sqrtf(1 - powf(planets[i].eccentricity, 2));
            float y = b * std::sinf(planets[i].angle);

            planets[i].setPosition({orbitCenter.x + x, orbitCenter.y + y});
        }

        window.setView(view); // apply view before drawing

        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(sun);

        for (int i = 0; i < planets.size(); i++)
        {
            window.draw(planets[i].shape);

            const int pointCount = 360;
            sf::VertexArray ellipse(sf::PrimitiveType::LineStrip, pointCount + 1);

            for (int j = 0; j <= pointCount; j++)
            {
                float angle = j * 2 * PI / pointCount; // radians
                float x = planets[i].semiMajorXAxis * std::cosf(angle);
                float b = planets[i].semiMajorXAxis * std::sqrtf(1 - powf(planets[i].eccentricity, 2));
                float y = b * std::sinf(angle);

                ellipse[j].position = sf::Vector2f{orbitCenter.x + x, orbitCenter.y + y};
            }

            window.draw(ellipse);
        }

        // end the current frame
        window.display();
    }

    return 0;
}
