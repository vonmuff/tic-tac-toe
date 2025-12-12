//
// Created by user on 11.12.2025.
//

#include "Game/Game.h"

void Game::welcome() {
    std::cout << "      ________   _     _____     ________     ____    _    __      _     _        ____        ______\n";
    std::cout << "     /_______/  |_|   |  __/    /_______/    / /| |  | |  / /     | |   | |    __/    \\__    |  ___/\n";
    std::cout << "        | |      _   |  |          | |      / / | |  | | / /      | |   | |   /    __    \\   | /    \n";
    std::cout << "        | |     | |  | |           | |     / /  | |  | |/ /       | |___| |  /    /  \\    \\  | |____\n";
    std::cout << "        | |     | |  | |           | |    / /___| |  | |\\ \\       | |   | |  \\_   \\__/   _/  | ____/\n";
    std::cout << "        | |     | |  |  |__        | |   / /    | |  | | \\ \\      | |   | |    \\_      _/    | \\_____\n";
    std::cout << "        |_|     |_|   |____\\       |_|  /_/     |_|  |_|  \\_\\     |_|   |_|      \\____/      |______/\n";

    std::cout <<"\n\n Press any button to continue ...\n";
    char presskey;
    if (std::cin >> presskey)
        system("cls");
}

void Game::render() const {
    for (auto &str : map) {
        std::cout << str;
    }
}

void Game::render(int row, int colm) {
    size_t patternRow = 5 + (5*row) + row;
    size_t patternColm = 9 + (9*colm) + colm;

    size_t iterRow{0}, iterColm{0};

    switch (patternVariant) {
        case 0: {
            for (size_t mapRow = 1+(5*row) + row; mapRow <= patternRow; ++mapRow, ++iterRow) {
                for (size_t mapColm = 1+(9*colm)+colm; mapColm <= patternColm; ++mapColm, ++iterColm) {
                    map[mapRow][mapColm] = zeroPattern[iterRow][iterColm];
                }
                iterColm = 0;
            }
            ++patternVariant;
            break;
        }
        case 1: {
            for (size_t mapRow = 1+(5*row) + row; mapRow <= patternRow; ++mapRow, ++iterRow) {
                for (size_t mapColm = 1+(9*colm)+colm; mapColm <= patternColm; ++mapColm, ++iterColm) {
                    map[mapRow][mapColm] = crossPattern[iterRow][iterColm];
                }
                iterColm = 0;
            }
            --patternVariant;
            break;
        }
    }
}

void Game::step() {
    std::cout << "Enter position on map: ";
    std::cin >> positionMap.first >> positionMap.second;
    while (true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Enter a number between (0-2): ";
            std::cin >> positionMap.first >> positionMap.second;
        }
        else if (implementationMap[positionMap.first][positionMap.second] == 0) {
            implementationMap[positionMap.first][positionMap.second] = 1;
            break;
        }
        else {
            std::cout << "This field is already taken.\n Please select another one: ";
            std::cin >> positionMap.first >> positionMap.second;
        }

    }
    render(positionMap.first, positionMap.second);
    render();
}
