#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Particle
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float mass;
    float radius;

    Particle(float r, sf::Vector2f pos, sf::Vector2f vel, float m, sf::Color color)
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

sf::Vector2f normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    return len == 0 ? sf::Vector2f(0, 0) : v / len;
}

float dot(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

void resolveCollision(Particle &a, Particle &b)
{
    sf::Vector2f posA = a.getPosition();
    sf::Vector2f posB = b.getPosition();
    sf::Vector2f normal = normalize(posB - posA);

    sf::Vector2f relativeVel = b.velocity - a.velocity;
    float velAlongNormal = dot(relativeVel, normal);

    if (velAlongNormal > 0)
        return;

    // float e = 1.0f; // elastic
    float e = 0.5f;

    float j = -(1 + e) * velAlongNormal;
    j /= (1 / a.mass + 1 / b.mass);

    sf::Vector2f impulse = j * normal;
    a.velocity -= impulse / a.mass;
    b.velocity += impulse / b.mass;

    float dist = std::sqrt((posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y));
    float overlap = (a.radius + b.radius) - dist;
    sf::Vector2f correction = normal * (overlap / 2.0f);

    // more advance: two balls have different mass
    float totalInvMass = 1.0 / a.mass + 1.0 / b.mass;

    a.setPosition(posA - (correction * (float)(1.0 / a.mass) / totalInvMass));
    b.setPosition(posB + (correction * (float)(1.0 / b.mass) / totalInvMass));
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Particle Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    const int count = 50;

    for (int i = 0; i < count; ++i)
    {
        float r = 5 + std::rand() % 10;
        float x = r + std::rand() % (800 - int(2 * r));
        float y = r + std::rand() % (600 - int(2 * r));
        float vx = (std::rand() % 200 - 100);
        float vy = (std::rand() % 200 - 100);
        float m = r;
        sf::Color color(rand() % 255, rand() % 255, rand() % 255);

        particles.emplace_back(r, sf::Vector2f(x, y), sf::Vector2f(vx, vy), m, color);
    }

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

        // Update
        for (auto &p : particles)
        {
            p.update(dt);

            sf::Vector2f pos = p.getPosition();
            if (pos.x < p.radius || pos.x + (2 * p.radius) > 800)
                p.velocity.x *= -1;
            if (pos.y < p.radius || pos.y + (2 * p.radius) > 600)
                p.velocity.y *= -1;
        }

        // Check collisions
        for (size_t i = 0; i < particles.size(); ++i)
        {
            for (size_t j = i + 1; j < particles.size(); ++j)
            {
                sf::Vector2f delta = particles[j].getPosition() - particles[i].getPosition();
                float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
                if (dist < particles[i].radius + particles[j].radius)
                {
                    resolveCollision(particles[i], particles[j]);
                }
            }
        }

        // Render
        window.clear(sf::Color::Black);
        for (auto &p : particles)
        {
            window.draw(p.shape);
        }
        window.display();
    }

    return 0;
}
