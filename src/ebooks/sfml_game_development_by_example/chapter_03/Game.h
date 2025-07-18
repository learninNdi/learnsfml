#pragma once
#include "Window.h"
#include "Snake.h"
#include "World.h"
#include "Textbox.h"

class Game
{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();

    Window *GetWindow();

    sf::Time GetElapsed();
    void RestartClock();

private:
    Window m_window;

    sf::Clock m_clock;
    float m_elapsed;

    Snake m_snake;
    World m_world;

    Textbox m_textbox;
};
