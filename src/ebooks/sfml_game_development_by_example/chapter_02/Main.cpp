#include "Game.h"

int main()
{
    // program entry point
    Game game; // creating our game object
    while (!game.GetWindow()->isDone())
    {
        // game loop
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock(); // restarting our clock
    }

    return 0;
}
