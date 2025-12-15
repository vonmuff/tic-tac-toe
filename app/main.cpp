#include <iostream>
#include "Game/Game.h"

int main() {
    Game game;
    game.welcome();
    while (game.is_running()) {
        game.step();
    }
    return 0;
}
