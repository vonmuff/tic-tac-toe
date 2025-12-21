//
// Created by user on 11.12.2025.
//

#include "Game/Game.h"
#include <algorithm>
#include <ranges>

void Game::welcome() const {
    std::cout << R"(
   ________   _     _____     ________     ____     _____     ________    _______     ______
  /_______/  |_|   |  __/    /_______/    / /| |   |  __/    /_______/   /  ___  \   | ____/
     | |      _   |  |          | |      / / | |  |  |          | |     |  /   \  |  | /
     | |     | |  | |           | |     / /  | |  | |           | |     |  |   |  |  | |____
     | |     | |  | |           | |    / /___| |  | |           | |     |  |   |  |  | ____/
     | |     | |  |  |__        | |   / /    | |  |  |__        | |     |  \___/  |  | \_____
     |_|     |_|   |____\       |_|  /_/     |_|   |____\       |_|      \_______/   |______/)";

    std::cout << "\n\n Press any button to continue\n\n: ";
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
    int iterRow{0}, iterColm{0};
    for (size_t row{0}; row <= Const::ROWS_MAP; ++row) {
        for (size_t colm{0}; colm != Const::COLMS_MAP; ++colm) {
            if (row % Const::SEPARATOR_ROWS_MAP == 0) {
                iterRow = 0;
                if (colm % Const::SEPARATOR_COLMS_MAP == 0) {
                    std::cout << " ";
                    continue;
                }
                std::cout <<"-";
                continue;
            }
            if (colm % Const::SEPARATOR_COLMS_MAP == 0) {
                std::cout << "|";
                iterColm = 0;
                continue;
            }
            if (implementationMap[row / Const::SEPARATOR_ROWS_MAP][colm / Const::SEPARATOR_COLMS_MAP] != 0) {
                if (implementationMap[row / Const::SEPARATOR_ROWS_MAP][colm / Const::SEPARATOR_COLMS_MAP] == Const::CROSS_PATTERN)
                    std::cout << crossPattern[iterRow][iterColm];
                if (implementationMap[row / Const::SEPARATOR_ROWS_MAP][colm / Const::SEPARATOR_COLMS_MAP] == Const::ZERO_PATTERN)
                    std::cout << zeroPattern[iterRow][iterColm];
            }
            else
                std::cout << " ";
            ++iterColm;

        }
        std::cout << "  \n";
        if (row % Const::SEPARATOR_ROWS_MAP != 0)
            ++iterRow;
    }
}

void Game::enter() {
    int number;
    std::cout << "Enter position on map: ";
    while (true) {
        std::cin >> number;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Enter a number between (1-9): ";
            continue;
        } else if (number < 1 || number > 9) {
            std::cout << "Enter a number between (1-9): ";
            continue;
        }
        --number;
        positionMap.first = 2 - (number / 3);
        positionMap.second = number % 3;
        std::cin.ignore(32767, '\n');
        if (implementationMap[positionMap.first][positionMap.second] == 0) {
            implementationMap[positionMap.first][positionMap.second] = patternVariant;
            break;
        } else {
            std::cout << "This field is already taken.\nPlease select another one: ";
            continue;
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
    patternVariant = (patternVariant == Const::CROSS_PATTERN) ? Const::ZERO_PATTERN : Const::CROSS_PATTERN;
    ++stepCount;
}

std::optional<bool> Game::win() {
    if (stepCount >= Const::MIN_WIN_STEP || stepCount <= Const::MAX_WIN_STEP) {
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
    for (size_t row{0}; row != Const::MAP_SIZE; ++row) {
        std::ranges::fill(implementationMap[row], 0);
    }
}

bool Game::is_running() const {
    return isRunning;
}

bool Game::start_over() {
    std::cout << "\nWould you like to continue playing?\n";
    std::cout << "Press y - continue  n - quit\n\n: ";
    char presskey;
    while(true) {
        std::cin >> presskey;
        if (presskey != 'y' && presskey != 'Y' && presskey != 'n' && presskey != 'N' ) {
            std::cout << "Enter y or n: ";
            continue;
        }
        if (presskey == 'y' || presskey == 'Y') {
            isRunning = true;
            clear_map();
            stepCount = 1;
            return true;
        } else if (presskey == 'n' || presskey == 'N') {
            return false;
        }
    }
}
