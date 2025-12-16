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

    void choose();

    void render() const;

    void step();

    bool is_running() const;

private:
    void enter();

    void place_pattern(int, int);

    std::optional<bool> win();

    bool is_win(std::span<int>);

    struct Const {
        inline static constexpr int ROWS_PATTERN{5};
        inline static constexpr int COLMS_PATTERN{9};
        inline static constexpr int CROSS_PATTERN{1};
        inline static constexpr int ZERO_PATTERN{2};
        inline static constexpr int MAP_SIZE{3};
        inline static constexpr int MIN_WIN_STEP{5};
        inline static constexpr int MAX_WIN_STEP{9};
    };

    bool isRunning{true};
    int patternVariant{1};
    int stepCount{1};
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

    std::vector<std::string> map{
        {" --------- --------- --------- \n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {" --------- --------- --------- \n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {" --------- --------- --------- \n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {"|         |         |         |\n"},
        {" --------- --------- --------- \n"},
    };
};


#endif //TICTACHOE_GAME_H
