//
// Created by user on 11.12.2025.
//

#include "Game/Game.h"
#include <algorithm>
#include <ranges>

void Game::welcome() const {
    std::cout << R"(
                     ________   _     _____     ________     ____    _    __     ________    _______     ______
                    /_______/  |_|   |  __/    /_______/    / /| |  | |  / /    /_______/   /  ___  \   | ____/
                       | |      _   |  |          | |      / / | |  | | / /        | |     |  /   \  |  | /
                       | |     | |  | |           | |     / /  | |  | |/ /         | |     |  |   |  |  | |____
                       | |     | |  | |           | |    / /___| |  | |\ \         | |     |  |   |  |  | ____/
                       | |     | |  |  |__        | |   / /    | |  | | \ \        | |     |  \___/  |  | \_____
                       |_|     |_|   |____\       |_|  /_/     |_|  |_|  \_\       |_|      \_______/   |______/)";

    std::cout << "\n\n Press any button to continue ...\n";
    char presskey;
    if (std::cin >> presskey)
        system("cls");
}

void Game::choose() {
    std::cout << "Choose the pattern that will start first \n\n";
    std::cout << "1 - cross     2 - zero\n\n";
    for (size_t row{0}; row != Const::ROWS_PATTERN; ++row) {
        for (size_t colm{0}; colm != Const::COLMS_PATTERN; ++colm) {
            std::cout << crossPattern[row][colm];
        }
        std::cout << "    ";
        for (size_t colm{0}; colm != Const::COLMS_PATTERN; ++colm) {
            std::cout << zeroPattern[row][colm];
        }
        std::cout << "\n";
    }
    int firstPattern;
    std::cout << "\n: ";
    while (true) {
        std::cin >> firstPattern;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Enter a number (1-2): ";
            continue;
        } else if (firstPattern < 1 || firstPattern > 2) {
            std::cout << "Enter a number (1-2): ";
            continue;
        }
        patternVariant = firstPattern;
        break;
    }
}

void Game::render() const {
    system("cls");
    for (auto &str: map) {
        std::cout << str;
    }
}

void Game::enter() {
    std::cout << "Enter position on map: ";
    while (true) {
        std::cin >> positionMap.first >> positionMap.second;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Enter a number between (0-2): ";
            continue;
        } else if ((positionMap.first < 0 || positionMap.first > 2) || (positionMap.second < 0 || positionMap.second > 2)) {
            std::cout << "Enter a number between (0-2): ";
            continue;
        } else if (implementationMap[positionMap.first][positionMap.second] == 0) {
            break;
        } else {
            std::cout << "This field is already taken.\n Please select another one: ";
            continue;
        }
    }
}

void Game::place_pattern(int row, int colm) {
    size_t patternRow = Const::ROWS_PATTERN + (Const::ROWS_PATTERN * row) + row;
    size_t patternColm = Const::COLMS_PATTERN + (Const::COLMS_PATTERN * colm) + colm;

    size_t iterRow{0}, iterColm{0};

    const std::vector<std::string> *ptr = nullptr;

    if (patternVariant == Const::CROSS_PATTERN)
        ptr = &crossPattern;
    if (patternVariant == Const::ZERO_PATTERN)
        ptr = &zeroPattern;
    for (size_t mapRow = 1 + (Const::ROWS_PATTERN * row) + row; mapRow <= patternRow; ++mapRow, ++iterRow) {
        for (size_t mapColm = 1 + (Const::COLMS_PATTERN * colm) + colm; mapColm <= patternColm; ++mapColm, ++iterColm) {
            map[mapRow][mapColm] = (*ptr)[iterRow][iterColm];
        }
        iterColm = 0;
    }
    implementationMap[positionMap.first][positionMap.second] = patternVariant;
}

void Game::step() {
    render();
    if (win().has_value()) {
        isRunning = false;
        return;
    }
    enter();
    place_pattern(positionMap.first, positionMap.second);
    patternVariant = (patternVariant == Const::CROSS_PATTERN) ? Const::ZERO_PATTERN : Const::CROSS_PATTERN;
    ++stepCount;
}

std::optional<bool> Game::win() {
    if (stepCount >= Const::MIN_WIN_STEP && stepCount < Const::MAX_WIN_STEP) {
        std::array<int, Const::MAP_SIZE> temp{0};
        for (size_t row{0}; row != Const::MAP_SIZE; ++row) {
            if (is_win(implementationMap[row])) { return true; }
        }
        for (size_t colm{0}; colm != Const::MAP_SIZE; ++colm) {
            for (size_t row{0}; row != Const::MAP_SIZE; ++row) {
                temp[row] = implementationMap[row][colm];
            }
            if (is_win(temp)) { return true; }
        }
        for (size_t row{0}, colm{0}; row != Const::MAP_SIZE; ++row, ++colm) {
            temp[row] = implementationMap[row][colm];
        }
        if (is_win(temp)) { return true; }
        for (size_t row{0}, colm{2}; row != Const::MAP_SIZE; ++row, --colm) {
            temp[row] = implementationMap[row][colm];
        }
        if (is_win(temp)) { return true; }
    }
    if (stepCount > Const::MAX_WIN_STEP) {
        std::cout << "It was a draw...\n";
        return false;
    }
    return std::nullopt;
}

bool Game::is_win(std::span<int> temp) {
    for (size_t patternVar{1}; patternVar <= 2; ++patternVar) {
        if (std::ranges::all_of(temp, [&patternVar](int i) { return i == patternVar; })) {
            patternVar == Const::CROSS_PATTERN ? std::cout << "The crosses won!\n" : std::cout << "The zeros won!\n";
            return true;
        }
    }
    return false;
}

void Game::clear_map() {
    char space = ' ';
    for (size_t row{1}; row != 18; ++row) {
        if (row % 6 == 0)
            continue;
        for (size_t colm{1}; colm != 31; ++colm) {
            if (colm % 10 == 0)
                continue;
            map[row][colm] = space;
        }
    }
}

bool Game::is_running() const {
    return isRunning;
}

bool Game::start_over() {
    std::cout << "Would you like to continue playing?\n";
    std::cout << "Press y - continue  n - quit\n\n :";
    char presskey;
    std::cin >> presskey;
    if (presskey == 'y') {
    }
    if (presskey == 'n') {
    }
}
