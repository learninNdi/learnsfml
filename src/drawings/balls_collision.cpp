#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f velocity;
    float mass;
    float radius;

    Ball(float r, sf::Vector2f vel, float m, sf::Color color)
    {
        radius = r;
        velocity = vel;
        mass = m;

        ball.setRadius(radius);
        ball.setOrigin({radius, radius});
        float x = rand() % SCR_WIDTH - radius;
        float y = rand() % SCR_HEIGHT - radius;
        ball.setPosition({x, y});
        ball.setFillColor(color);
    }

    void update(float dt)
    {
        ball.move(velocity * dt);
    }

    sf::Vector2f getPosition() const
    {
        return ball.getPosition();
    }

    void setPosition(sf::Vector2f pos)
    {
        ball.setPosition(pos);
    }
};

sf::Vector2f normalize(sf::Vector2f v)
{
    float len = std::sqrtf(v.x * v.x + v.y * v.y);

    return len == 0 ? sf::Vector2f(0, 0) : v / len;
}

float dot(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

void collision(Ball &a, Ball &b)
{
    sf::Vector2f posA = a.getPosition();
    sf::Vector2f posB = b.getPosition();
    sf::Vector2f normal = normalize(posB - posA); // get the direction of length just 1

    sf::Vector2f relativeVel = b.velocity - a.velocity;
    float velAlongNormal = dot(relativeVel, normal);

    if (velAlongNormal > 0)
        return; // the ball face the same direction

    float e = 1.0f;

    float j = -(1 + e) * velAlongNormal;
    j /= (1 / a.mass + 1 / b.mass);

    sf::Vector2f impulse = j * normal;
    a.velocity -= impulse / a.mass;
    b.velocity += impulse / b.mass;

    float dist = std::sqrtf((posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y));
    float overlap = (a.radius + b.radius) - dist;
    sf::Vector2f correction = normal * (overlap / 2.0f);

    // more advance: two balls have different mass
    float totalInvMass = 1.0 / a.mass + 1.0 / b.mass;

    a.setPosition(posA - (correction * (float)(1.0 / a.mass) / totalInvMass));
    b.setPosition(posB + (correction * (float)(1.0 / b.mass) / totalInvMass));
}

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

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // BallSystem balls;
    std::vector<Ball> balls;
    const int count = 50;

    for (int i = 0; i < count; i++)
    {
        float r = 5 + std::rand() % 10;
        float x = r + std::rand() % (SCR_WIDTH - int(2 * r));
        float y = r + std::rand() % (SCR_HEIGHT - int(2 * r));
        float vx = (std::rand() % 200 - 100);
        float vy = (std::rand() % 200 - 100);
        float m = r;
        sf::Color color(rand() % 255, rand() % 255, rand() % 255);

        balls.emplace_back(r, sf::Vector2f({vx, vy}), m, color);
    }

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        // check all the window's events that were triggered since the last iteration of the loop
        // / handle events
        while (const std::optional event = window.pollEvent())
        {
            // when close button is clicked
            // or when escape button is pressed
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        for (auto &ball : balls)
        {
            ball.update(dt);

            sf::Vector2f pos = ball.getPosition();
            if (pos.x < ball.radius || pos.x > SCR_WIDTH - ball.radius)
                ball.velocity.x *= -1;

            if (pos.y < ball.radius || pos.y > SCR_HEIGHT - ball.radius)
                ball.velocity.y *= -1;
        }

        // check collisions
        for (int i = 0; i < balls.size(); i++)
        {
            for (int j = i + 1; j < balls.size(); j++)
            {
                sf::Vector2f delta = balls[j].getPosition() - balls[i].getPosition();
                float dist = std::sqrtf(delta.x * delta.x + delta.y * delta.y);
                if (dist < balls[i].radius + balls[j].radius)
                    collision(balls[i], balls[j]);
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (auto &ball : balls)
            window.draw(ball.ball);

        // end the current frame
        window.display();
    }

    return 0;
}
