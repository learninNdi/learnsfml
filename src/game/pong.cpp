#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <unistd.h>

void createBall();
void createPlayer();

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 800;
double Pi = 3.1415926535897932384626433832795;
double epsilon = 1e-9;

std::random_device rd;
std::mt19937 rng(rd());

sf::CircleShape ball;
float ballRadius = 20;
float ballDir;
float ballSpeed = 2;
float playerSpeed = 8;
float enemySpeed = 8;

float xCenterWindow = SCR_WIDTH / 2;
float yCenterWindow = SCR_HEIGHT / 2;

sf::RectangleShape player1, enemy;
sf::Vector2f playerSize = {10, 80};

int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode({SCR_WIDTH, SCR_HEIGHT}), "Game Uler");
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

    createBall();
    createPlayer();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        // / handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                exit(0);

            if (const auto *keyboardPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyboardPressed->scancode == sf::Keyboard::Scancode::W)
                {
                    if (player1.getPosition().y >= 0)
                        player1.move({0, -playerSpeed});
                }
                else if (keyboardPressed->scancode == sf::Keyboard::Scancode::S)
                {
                    if (player1.getPosition().y + playerSize.y <= SCR_HEIGHT)
                        player1.move({0, playerSpeed});
                }
                // else if (keyboardPressed->scancode == sf::Keyboard::Scancode::Left)
                // {
                //     if (snakeDir != 0)
                //     {
                //         snakeDir = 180;
                //     }
                // }
                // else if (keyboardPressed->scancode == sf::Keyboard::Scancode::Right)
                // {
                //     if (snakeDir != 180)
                //     {
                //         snakeDir = 0;
                //     }
                // }

                if (keyboardPressed->scancode == sf::Keyboard::Scancode::Escape)
                    exit(0);

                if (keyboardPressed->scancode == sf::Keyboard::Scancode::R)
                {
                    createBall();
                    createPlayer();
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw
        window.draw(ball);
        window.draw(player1);
        window.draw(enemy);

        float nextXPos = cos(ballDir * Pi / 180);
        float nextYPos = sin(ballDir * Pi / 180);

        if (nextXPos > 0 && nextXPos < epsilon)
            nextXPos = 0;
        if (nextYPos > 0 && nextYPos < epsilon)
            nextYPos = 0;

        ball.move({nextXPos * ballSpeed, nextYPos * ballSpeed});

        if (ball.getPosition().x >= SCR_WIDTH - (2 * ballRadius))
        {
            if (ballDir == 0 || ballDir == 360)
                ballDir = 180;
            else if (ballDir > 0 && ballDir < 90)
                ballDir = 90 + (90 - ballDir);
            else if (ballDir > 270 && ballDir < 360)
                ballDir = 270 - (ballDir - 270);
        }
        else if (ball.getPosition().y >= SCR_HEIGHT - (2 * ballRadius))
        {
            if (ballDir == 90)
                ballDir = 270;
            else if (ballDir > 0 && ballDir < 90)
                ballDir = 360 - ballDir;
            else if (ballDir > 90 && ballDir < 180)
                ballDir = 180 + (180 - ballDir);
        }
        else if (ball.getPosition().x <= 0)
        {
            if (ballDir == 180)
                ballDir = 0;
            else if (ballDir > 180 && ballDir < 270)
                ballDir = 270 + (ballDir - 180);
            else if (ballDir > 90 && ballDir < 180)
                ballDir = 90 - (180 - ballDir);
        }
        else if (ball.getPosition().y <= 0)
        {
            if (ballDir == 270)
                ballDir = 90;
            else if (ballDir > 180 && ballDir < 270)
                ballDir = 180 - (ballDir - 180);
            else if (ballDir > 270 && ballDir < 360)
                ballDir = 360 - ballDir;
        }

        // enemy move
        // if ((ballDir >= 315 && ballDir <= 359) || ballDir == 0 || ballDir == 360)
        //     enemy.move({0, -enemySpeed});
        // else if (ballDir > 0 && ballDir <= 45)
        //     enemy.move({0, enemySpeed});

        // end the current frame
        window.display();
    }

    return 0;
}

void createBall()
{
    float dir[3] = {
        std::uniform_real_distribution(0.f, 315.f)(rng),
        std::uniform_real_distribution(0.f, 45.f)(rng),
        std::uniform_real_distribution(135.f, 225.f)(rng)};
    srand(time(NULL));
    // ballDir = dir[rand() % 3];
    ballDir = 0;
    ball.setRadius(ballRadius);
    ball.setPosition({xCenterWindow, xCenterWindow});
}

void createPlayer()
{
    player1.setSize(playerSize);
    player1.setPosition({0, (SCR_HEIGHT - playerSize.y) / 2});

    enemy.setSize(playerSize);
    enemy.setPosition({SCR_WIDTH - playerSize.x, (SCR_HEIGHT - playerSize.y) / 2});
}
