#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window
{
public:
    Window();
    Window(const std::string &title, const sf::Vector2u &size);
    ~Window();

    void BeginDraw(); // clear the window
    void EndDraw();   // display the changes

    void Update();

    bool isDone();
    bool IsFullScreen();
    sf::Vector2u GetWindowSize();
    sf::RenderWindow *GetRenderWindow();

    void ToggleFullScreen();

    void Draw(sf::Drawable &l_drawable);

private:
    void Setup(const std::string title, const sf::Vector2u &size);
    void Create();
    void Destroy();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullScreen;
};
