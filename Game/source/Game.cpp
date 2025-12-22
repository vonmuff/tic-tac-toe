//
// Created by user on 11.12.2025.
//

#include "Game/Game.h"
#include <algorithm>
#include <ranges>
#include <random>
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

void Game::game_mode() {
    std::cout << "Select a game mode\n";
    std::cout << R"(
Play with a friend - 1   Play with the computer - 2
  _        _              _
 |_|      |_|            |_|       _____
  |        |              |       |     |
 /|\  vs  /|\            /|\  vs  |_____|
  |        |              |      ____|____
 / \      / \            / \    |_________|)";
    std::cout << "\n\n:";
    while (true) {
         std::cin >> mode;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Enter a number (1-2): ";
            continue;
        } else if (mode < 1 || mode > 2) {
            std::cout << "Enter a number (1-2): ";
            continue;
        }
        break;
    }
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

void Game::computer_logic() {
    if (stepCount == 1) {
        if (implementationMap[1][1] == 0) {
            implementationMap[1][1] = Const::ZERO_PATTERN;
        }else if (implementationMap[1][1] == Const::CROSS_PATTERN) {
            std::vector<int> angles{6,8,0,2};
            random(angles);
            implementationMap[positionMap.first][positionMap.second] = Const::ZERO_PATTERN;
        }
        return;
    }

    for (int pattern{2}; pattern > 0; --pattern) {

        for (int row{0}; row != Const::MAP_SIZE; ++row) {
            if (range_check(implementationMap[row], pattern).has_value()){
                int index = range_check(implementationMap[row], pattern).value();
                implementationMap[row][index] = Const::ZERO_PATTERN;
                return;
            }
        }

        for (int colm{0}; colm != Const::MAP_SIZE; ++colm) {
            std::vector<int> temp(3);
            for (int row{0}; row != Const::MAP_SIZE; ++row){
                temp[row] = implementationMap[row][colm];
            }
            if (range_check(temp, pattern).has_value()) {
                int index = range_check(temp, pattern).value();
                implementationMap[index][colm] = Const::ZERO_PATTERN;
                return;
            }
        }

        std::vector<int> temp(3);
        for (int row{0}, colm{0}; row != Const::MAP_SIZE; ++row, ++colm){
            temp[row] = implementationMap[row][colm];
        }
        if (range_check(temp, pattern).has_value()){
            int index = range_check(temp, pattern).value();
            implementationMap[index][index] = Const::ZERO_PATTERN;
            return;
        }

        for (int row{0}, colm{2}; row != Const::MAP_SIZE; ++row, --colm){
            temp[row] = implementationMap[row][colm];
        }
        if (range_check(temp, pattern).has_value()){
            int index = range_check(temp, pattern).value();
            implementationMap[index][2 - index] = Const::ZERO_PATTERN;
            return;
        }
    }

    while (true) {
        std::vector<int> num{1,2,3,4,5,6,7,8,9};
        random(num);
        if (implementationMap[positionMap.first][positionMap.second] == 0) {
            implementationMap[positionMap.first][positionMap.second] = Const::ZERO_PATTERN;
            break;
        }
    }
}

std::optional<int> Game::range_check(std::span<int> range, int pattern) {
    if (std::ranges::count(range, pattern) == 2) {
        auto pos = std::ranges::find(range, 0);
        if (pos != range.end()) {
            size_t index = std::ranges::distance(range.begin(), pos);
            return index;
        }
    }
    return std::nullopt;
}

void Game::random(std::span<int> temp) {
    std::random_device Seeder;
    std::mt19937 gen(Seeder());
    std::uniform_int_distribution<int> dist(0, temp.size() - 1);
    int randomPos = temp[dist(gen)];
    positionMap.first = 2 - (randomPos / 3);
    positionMap.second = randomPos % 3;

}

void Game::step() {
    render();
    enter();
    ++stepCount;
    win();
    if_win();
    if (is_running() == false) return;;
    if (mode == 2) {
        computer_logic();
        ++stepCount;
        win();
        if_win();
        if (is_running() == false) return;;
    } else {
        patternVariant = (patternVariant == Const::CROSS_PATTERN) ? Const::ZERO_PATTERN : Const::CROSS_PATTERN;
    }
}

void Game::win() {
    if (stepCount >= Const::MIN_WIN_STEP && stepCount <= Const::MAX_WIN_STEP) {
        std::array<int, Const::MAP_SIZE> temp{0};
        for (size_t row{0}; row != Const::MAP_SIZE; ++row) {
            if (is_win(implementationMap[row])) { isWin = true; return; }
        }
        for (size_t colm{0}; colm != Const::MAP_SIZE; ++colm) {
            for (size_t row{0}; row != Const::MAP_SIZE; ++row) {
                temp[row] = implementationMap[row][colm];
            }
            if (is_win(temp)) { isWin = true; return; }
        }
        for (size_t row{0}, colm{0}; row != Const::MAP_SIZE; ++row, ++colm) {
            temp[row] = implementationMap[row][colm];
        }
        if (is_win(temp)) { isWin = true; return; }
        for (size_t row{0}, colm{2}; row != Const::MAP_SIZE; ++row, --colm) {
            temp[row] = implementationMap[row][colm];
        }
        if (is_win(temp)) { isWin = true; return; }
    }
    if (stepCount == Const::MAX_WIN_STEP) {
        isWin= false;
        return;
    }
    isWin = std::nullopt;

}

bool Game::is_win(std::span<int> temp) {
    for (size_t patternVar{1}; patternVar <= 2; ++patternVar) {
        if (std::ranges::all_of(temp, [&patternVar](int i) { return i == patternVar; })) {
            return true;
        }
    }
    return false;
}

void Game::if_win() {
    if (isWin.has_value()) {
        if (isWin.value() == true) {
            render();
            patternVariant == Const::CROSS_PATTERN ? std::cout << "The crosses won!\n" : std::cout << "The zeros won!\n";
        }
        else if (isWin.value() == false) {
            render();
            std::cout << "It was a draw...\n";
        }
        isRunning = false;
    }
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
