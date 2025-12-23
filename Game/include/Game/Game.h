//
// Created by user on 11.12.2025.
//

#ifndef TICTACHOE_GAME_H
#define TICTACHOE_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <array>
#include <span>
#include <optional>

class Game {
public:
    void welcome() const;

    void game_mode();

    void choose();

    void render() const;

    void step();

    bool is_running() const;

    bool start_over();

private:
    void enter();

    void computer_logic();

    std::optional<int> range_check(std::span<int> range, int pattern);

    void random(std::span<int>);

    void win();

    bool is_win(std::span<int>);

    void if_win();

    void clear_map();

    struct Const {
        inline static constexpr int ROWS_PATTERN{5};
        inline static constexpr int COLMS_PATTERN{9};
        inline static constexpr int CROSS_PATTERN{1};
        inline static constexpr int ZERO_PATTERN{2};
        inline static constexpr int MAP_SIZE{3};
        inline static constexpr int MIN_WIN_STEP{5};
        inline static constexpr int MAX_WIN_STEP{9};
        inline static constexpr int ROWS_MAP{18};
        inline static constexpr int COLMS_MAP{31};
        inline static constexpr int SEPARATOR_ROWS_MAP{6};
        inline static constexpr int SEPARATOR_COLMS_MAP{10};
    };

    bool isRunning{true};
    std::optional<bool> isWin;
    int mode{1};
    int patternVariant;
    int firstPattern;
    int stepCount{0};
    std::pair<int, int> positionMap;
    std::array<std::array<int, 3>, 3> implementationMap{};

    std::vector<std::string> crossPattern{
        {"  *   *  "},
        {"   * *   "},
        {"    *    "},
        {"   * *   "},
        {"  *   *  "}
    };

    std::vector<std::string> zeroPattern{
        {"   ***   "},
        {"  *   *  "},
        {" *     * "},
        {"  *   *  "},
        {"   ***   "}
    };

};


#endif //TICTACHOE_GAME_H
