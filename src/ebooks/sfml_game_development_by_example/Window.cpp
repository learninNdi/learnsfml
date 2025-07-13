#include "Window.h"

unsigned int SCR_HEIGHT = 768;
unsigned int SCR_WIDTH = 1024;

Window::Window() { Setup("Window", sf::Vector2u(SCR_WIDTH, SCR_HEIGHT)); }

Window::Window(const std::string &l_title, const sf::Vector2u &l_size) { Setup(l_title, l_size); }

Window::~Window() { Destroy(); }

void Window::Setup(const std::string l_title, const sf::Vector2u &l_size)
{
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullScreen = false;
    m_isDone = false;
    Create();
}

void Window::Create()
{
    auto style = m_isFullScreen ? sf::State::Fullscreen : sf::State::Windowed;
    m_window.create(sf::VideoMode({m_windowSize.x, m_windowSize.y}, 32), m_windowTitle, style);
}

void Window::Destroy() { m_window.close(); }

void Window::Update()
{
    while (const std::optional event = m_window.pollEvent())
    {
        // when close button is clicked
        if (event->is<sf::Event::Closed>())
            m_isDone = true;
        else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::F5)
                ToggleFullScreen();
        }
    }
}

void Window::ToggleFullScreen()
{
    m_isFullScreen = !m_isFullScreen;
    Destroy();
    Create();
}

void Window::BeginDraw() { m_window.clear(sf::Color::Black); }
void Window::EndDraw() { m_window.display(); }

bool Window::isDone() { return m_isDone; }
bool Window::IsFullScreen() { return m_isFullScreen; }
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

void Window::Draw(sf::Drawable &l_drawable) { m_window.draw(l_drawable); }
