#include <SFML/Graphics.hpp>
#include <cmath>

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float mass;
    float radius;

    Ball(float r, sf::Vector2f pos, sf::Vector2f vel, float m, sf::Color color)
    {
        radius = r;
        velocity = vel;
        mass = m;

        shape.setRadius(radius);
        shape.setOrigin({radius, radius});
        shape.setPosition(pos);
        shape.setFillColor(color);
    }

    void update(float dt)
    {
        shape.move(velocity * dt);
    }

    sf::Vector2f getPosition() const
    {
        return shape.getPosition();
    }

    void setPosition(sf::Vector2f pos)
    {
        shape.setPosition(pos);
    }
};

// Utility: Normalize vector
sf::Vector2f normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    return len == 0 ? sf::Vector2f(0, 0) : v / len;
}

// Utility: Dot product
float dot(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

// Collision response
void resolveCollision(Ball &a, Ball &b)
{
    sf::Vector2f posA = a.getPosition();
    sf::Vector2f posB = b.getPosition();
    sf::Vector2f normal = normalize(posB - posA);

    sf::Vector2f relativeVel = b.velocity - a.velocity;
    float velAlongNormal = dot(relativeVel, normal);

    if (velAlongNormal > 0)
        return; // balls are moving apart

    float e = 1.0f; // coefficient of restitution (1 = elastic)

    float j = -(1 + e) * velAlongNormal;
    j /= (1 / a.mass + 1 / b.mass);

    sf::Vector2f impulse = j * normal;
    a.velocity -= impulse / a.mass;
    b.velocity += impulse / b.mass;

    // Optional: correct overlap
    float dist = std::sqrt((posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y));
    float overlap = (a.radius + b.radius) - dist;
    sf::Vector2f correction = normal * (overlap / 2.0f);
    a.setPosition(posA - correction);
    b.setPosition(posB + correction);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Ball Collision");

    Ball ball1(30, {200, 300}, {200, 0}, 1.0f, sf::Color::Blue);
    Ball ball2(30, {600, 300}, {-200, 0}, 1.0f, sf::Color::Green);

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            // when close button is clicked
            // or when escape button is pressed
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        // Update positions
        ball1.update(dt);
        ball2.update(dt);

        // Check for collision
        sf::Vector2f delta = ball2.getPosition() - ball1.getPosition();
        float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        if (dist <= ball1.radius + ball2.radius)
        {
            resolveCollision(ball1, ball2);
        }

        // Wall bounce
        for (Ball *b : {&ball1, &ball2})
        {
            sf::Vector2f pos = b->getPosition();
            if (pos.x - b->radius < 0 || pos.x + b->radius > 800)
                b->velocity.x *= -1;
            if (pos.y - b->radius < 0 || pos.y + b->radius > 600)
                b->velocity.y *= -1;
        }

        // Draw
        window.clear(sf::Color::White);
        window.draw(ball1.shape);
        window.draw(ball2.shape);
        window.display();
    }

    return 0;
}
