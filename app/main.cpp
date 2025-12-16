#include <iostream>
#include "Game/Game.h"

int main() {
    Game game;
    game.welcome();
    game.choose();
    while (game.is_running()) {
        game.step();
    }
    return 0;
}
