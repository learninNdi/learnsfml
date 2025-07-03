#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count) : m_particles(count), m_vertices(sf::PrimitiveType::Points, count)
    {
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle &p = m_particles[i];
            p.lifetime -= elapsed;

            // if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero)
                resetParticle(i);

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            m_vertices[i].color.a = static_cast<std::uint8_t>(ratio * 255);
        }
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = nullptr;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // create random number generator
        static std::random_device rd;
        static std::mt19937 rng(rd());

        // give a random velocity and lifetime to the particle
        const sf::Angle angle = sf::degrees(std::uniform_real_distribution(0.f, 360.f)(rng));
        const float speed = std::uniform_real_distribution(50.f, 100.f)(rng);
        m_particles[index].velocity = sf::Vector2f(speed, angle);
        m_particles[index].lifetime = sf::milliseconds(std::uniform_int_distribution(1000, 3000)(rng));

        // reset the position of the corresponding vertex
        m_vertices[index].position = m_emitter;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime{sf::seconds(3)};
    sf::Vector2f m_emitter;
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

    // create the particle system
    ParticleSystem particles(1000);

    // create a clock to track the elapsed time
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
        }

        // make the particle system emitter follow the mouse
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // update it
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(particles);

        // end the current frame
        window.display();
    }

    return 0;
}
