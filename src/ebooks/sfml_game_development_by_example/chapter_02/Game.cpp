#include "Game.h"

#include <iostream>

// Game::Game() : m_mushroom(m_mushroomTexture), m_window("Chapter 2", sf::Vector2u(1024, 768))
Game::Game() : m_window("Snake", sf::Vector2u(1024, 768)), m_mushroomTexture("../assets/img/Mushroom.png"), m_mushroom(m_mushroomTexture)
{
    RestartClock();
    srand(time(NULL));

    m_increment = sf::Vector2i(400, 400);
}

Game::~Game() {}

void Game::HandleInput()
{
    // input handling
}

void Game::Update()
{
    m_window.Update(); // update window events
    MoveMushroom();
}

void Game::MoveMushroom()
{
    sf::Vector2u l_windSize = m_window.GetWindowSize();
    sf::Vector2u l_textSize = m_mushroomTexture.getSize();

    if ((m_mushroom.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
        (m_mushroom.getPosition().x < 0 && m_increment.x < 0))
        m_increment.x *= -1;

    if ((m_mushroom.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
        (m_mushroom.getPosition().y < 0 && m_increment.y < 0))
        m_increment.y *= -1;

    float fElapsed = m_elapsed.asSeconds();

    m_mushroom.setPosition({m_mushroom.getPosition().x + (m_increment.x * fElapsed),
                            m_mushroom.getPosition().y + (m_increment.y * fElapsed)});
}

void Game::Render()
{
    m_window.BeginDraw(); // clear
    m_window.Draw(m_mushroom);
    m_window.EndDraw(); // display
}

sf::Time Game::GetElapsed() { return m_elapsed; }
void Game::RestartClock() { m_elapsed = m_clock.restart(); }
Window *Game::GetWindow() { return &m_window; }
