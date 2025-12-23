#include <iostream>
#include "Game/Game.h"

int main() {
    Game game;
    game.welcome();
    game.user_choise();
    bool flag{true};
    while (flag) {
        game.step();
        if (game.is_running() == false) {
            if (!game.start_over()) { flag = false; }
        }
    }
    return 0;
}
