//
// Created by user on 11.12.2025.
//

#include "Game/Game.h"
#include <algorithm>
#include <ranges>
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
    system("cls");
    for (auto &str : map) {
        std::cout << str;
    }
}

void Game::enter() {
    std::cout << "Enter position on map: ";
    std::cin >> positionMap.first >> positionMap.second;
    while (true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Enter a number between (0-2): ";
            std::cin >> positionMap.first >> positionMap.second;
        }
        else if ((positionMap.first < 0 || positionMap.first > 2) && (positionMap.second < 0 || positionMap.second > 2)) {
            std::cout << "Enter a number between (0-2): ";
            std::cin >> positionMap.first >> positionMap.second;
        }
        else if (implementationMap[positionMap.first][positionMap.second] == 0) {
            break;
        }
        else {
            std::cout << "This field is already taken.\n Please select another one: ";
            std::cin >> positionMap.first >> positionMap.second;
        }
    }
}

void Game::render(int row, int colm) {
    size_t patternRow = Const::ROWS_PATTERN + (Const::ROWS_PATTERN*row) + row;
    size_t patternColm = Const::COLMS_PATTERN + (Const::COLMS_PATTERN*colm) + colm;

    size_t iterRow{0}, iterColm{0};

    switch (patternVariant) {
        case Const::CROSS_PATTERN: {
            for (size_t mapRow = 1+(Const::ROWS_PATTERN*row) + row; mapRow <= patternRow; ++mapRow, ++iterRow) {
                for (size_t mapColm = 1+(Const::COLMS_PATTERN*colm)+colm; mapColm <= patternColm; ++mapColm, ++iterColm) {
                    map[mapRow][mapColm] = crossPattern[iterRow][iterColm];
                }
                iterColm = 0;
            }
            implementationMap[positionMap.first][positionMap.second] = Const::CROSS_PATTERN;
            patternVariant = Const::ZERO_PATTERN;
            break;
        }
        case Const::ZERO_PATTERN: {
            for (size_t mapRow = 1+(Const::ROWS_PATTERN*row) + row; mapRow <= patternRow; ++mapRow, ++iterRow) {
                for (size_t mapColm = 1+(Const::COLMS_PATTERN*colm)+colm; mapColm <= patternColm; ++mapColm, ++iterColm) {
                    map[mapRow][mapColm] = zeroPattern[iterRow][iterColm];
                }
                iterColm = 0;
            }
            implementationMap[positionMap.first][positionMap.second] = Const::ZERO_PATTERN;
            patternVariant = Const::CROSS_PATTERN;
            break;
        }
    }
}

void Game::step() {
    render();
    if (win().has_value()) {
        isRunning = false;
        return;
    }
    enter();
    render(positionMap.first, positionMap.second);
    ++stepCount;
}
std::optional<bool> Game::win() { // to-do win renamed -> game_over
    if (stepCount >= Const::MIN_WIN_STEP && stepCount < Const::MAX_WIN_STEP) {
        std::array<int,3> temp{0};
        for (size_t row{0}; row != 3; ++row) {
            if (is_win(implementationMap[row])){ return true; }
        }
        for (size_t colm{0}; colm != 3; ++colm) {
            for (size_t row{0}; row != 3; ++row) {
                temp[row] = implementationMap[row][colm];
            }
            if (is_win(temp)){ return true; }
        }
        for (size_t row{0},colm{0}; row !=3; ++row, ++colm) {
            temp[row] = implementationMap[row][colm];
        }
        if (is_win(temp)){ return true; }
        for (size_t row{0},colm{2}; row !=3; ++row, --colm) {
            temp[row] = implementationMap[row][colm];
        }
        if (is_win(temp)){ return true; }
    }
    if (stepCount > Const::MAX_WIN_STEP) {
        std::cout << "It was a draw...\n";
        return false;
    }
    return std::nullopt;
}

bool Game::is_win(std::span<int> temp) {
    for (size_t patternVar{1}; patternVar <= 2; ++patternVar ) {
        if (std::ranges::all_of(temp, [&patternVar](int i){return i == patternVar;})) {
            patternVariant == 1 ? std::cout << "The crosses won!\n" : std::cout << "The zeros won!\n";
            return true;
        }
    }
    return false;
}

bool Game::is_running() const {
    return isRunning;
}
