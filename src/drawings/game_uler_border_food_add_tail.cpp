#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <unistd.h>

void createSnake();
void createFood();
void addTail();

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 1024;

int arrDir[4] = {0, 90, 180, 270};

std::random_device rd;
std::mt19937 rng(rd());

std::vector<sf::RectangleShape> snake;
float snakePartSize = 35;
float snakePartGap = 5;
float snakeDir;

sf::RectangleShape food;
float foodSize = 20;
int foodAvailable = 1;
float xFoodPos;
float yFoodPos;
sf::Color foodColor = sf::Color::Green;

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

    createSnake();
    sf::Vector2f lastPos;

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
                if (keyboardPressed->scancode == sf::Keyboard::Scancode::Up)
                {
                    if (snakeDir != 90)
                    {
                        snakeDir = 270;
                    }
                }
                else if (keyboardPressed->scancode == sf::Keyboard::Scancode::Down)
                {
                    if (snakeDir != 270)
                    {
                        snakeDir = 90;
                    }
                }
                else if (keyboardPressed->scancode == sf::Keyboard::Scancode::Left)
                {
                    if (snakeDir != 0)
                    {
                        snakeDir = 180;
                    }
                }
                else if (keyboardPressed->scancode == sf::Keyboard::Scancode::Right)
                {
                    if (snakeDir != 180)
                    {
                        snakeDir = 0;
                    }
                }

                if (keyboardPressed->scancode == sf::Keyboard::Scancode::Escape)
                    exit(0);

                if (keyboardPressed->scancode == sf::Keyboard::Scancode::R)
                {
                    snake.clear();
                    createSnake();
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw
        for (int i = 0; i < snake.size(); i++)
        {
            window.draw(snake[i]);

            if (i == 0)
            {
                lastPos = snake[0].getPosition();

                if (lastPos.x > SCR_WIDTH || lastPos.x + snakePartSize < 0 || lastPos.y > SCR_HEIGHT || lastPos.y + snakePartSize < 0)
                {
                    std::cout << "kalah" << std::endl;
                    exit(0); // lost
                }

                // if (lastPos.x)
                if ((xFoodPos > lastPos.x && xFoodPos < lastPos.x + snakePartSize) && (yFoodPos > lastPos.y && yFoodPos < lastPos.y + snakePartSize))
                {
                    foodAvailable = 0;
                    addTail();
                }

                // if (snakeDir == 0)
                // {
                //     snake[0].setPosition({(lastPos.x + snakePartSize + snakePartGap), lastPos.y});
                // }
                // else if (snakeDir == 90)
                // {
                //     snake[0].setPosition({lastPos.x, (snakePartSize + snakePartGap + lastPos.y)});
                // }
                // else if (snakeDir == 180)
                // {
                //     snake[0].setPosition({(lastPos.x - snakePartSize - snakePartGap), lastPos.y});
                // }
                // else if (snakeDir == 270)
                // {
                //     snake[0].setPosition({lastPos.x, (lastPos.y - snakePartSize - snakePartGap)});
                // }

                if (snakeDir == 0)
                {
                    snake[0].move({(snakePartSize + snakePartGap), 0});
                }
                else if (snakeDir == 90)
                {
                    snake[0].move({0, (snakePartSize + snakePartGap)});
                }
                else if (snakeDir == 180)
                {
                    snake[0].move({(-snakePartSize - snakePartGap), 0});
                }
                else if (snakeDir == 270)
                {
                    snake[0].move({0, (-snakePartSize - snakePartGap)});
                }
            }
            else
            {
                sf::Vector2f tempPos = snake[i].getPosition();
                snake[i].setPosition(lastPos);
                lastPos = tempPos;
            }
        }

        if (foodAvailable)
            window.draw(food);
        else
            createFood();

        usleep(800000);

        // end the current frame
        window.display();
    }

    return 0;
}

void createSnake()
{
    srand(time(NULL));
    snakeDir = arrDir[rand() % 4];
    // snakeDir = 180;

    createFood();

    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            float xPos = std::uniform_real_distribution(0.f + snakePartSize, SCR_WIDTH - snakePartSize)(rng);
            float yPos = std::uniform_real_distribution(0.f + snakePartSize, SCR_WIDTH - snakePartSize)(rng);
            sf::RectangleShape snakePart({snakePartSize, snakePartSize});
            snakePart.setFillColor(sf::Color::Red);
            snakePart.setPosition({xPos, yPos});
            snake.push_back(snakePart);
        }
        else
        {
            sf::RectangleShape snakePart({snakePartSize, snakePartSize});
            float xPos;
            float yPos;

            if (snakeDir == 0)
            {
                xPos = snake[0].getPosition().x - (i * snakePartSize) - (i * snakePartGap);
                yPos = snake[0].getPosition().y;
            }
            else if (snakeDir == 90)
            {
                xPos = snake[0].getPosition().x;
                yPos = snake[0].getPosition().y - (i * snakePartSize) - (i * snakePartGap);
            }
            else if (snakeDir == 180)
            {
                xPos = snake[0].getPosition().x + (i * snakePartSize) + (i * snakePartGap);
                yPos = snake[0].getPosition().y;
            }
            else if (snakeDir == 270)
            {
                xPos = snake[0].getPosition().x;
                yPos = snake[0].getPosition().y + (i * snakePartSize) + (i * snakePartGap);
            }

            snakePart.setPosition({xPos, yPos});
            snake.push_back(snakePart);
        }
    }
}

void createFood()
{
    food.setSize({foodSize, foodSize});
    xFoodPos = std::uniform_real_distribution(0.f + snakePartSize, SCR_WIDTH - snakePartSize)(rng);
    yFoodPos = std::uniform_real_distribution(0.f + snakePartSize, SCR_WIDTH - snakePartSize)(rng);
    food.setPosition({xFoodPos, yFoodPos});
    food.setFillColor(foodColor);
    foodAvailable = 1;
}

void addTail()
{
    sf::RectangleShape snakePart({snakePartSize, snakePartSize});
    float xPos = snake[snake.size() - 1].getPosition().x;
    float yPos = snake[snake.size() - 1].getPosition().y;
    snakePart.setPosition({xPos, yPos});
    snake.push_back(snakePart);
}
