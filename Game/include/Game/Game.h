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
class Game {
public:
    void welcome();

    void render() const;

    void render(int, int);

    void step();

    void win();

    bool is_win(std::span<int>);
private:
    int patternVariant{1}; // 1 = zeroPatter 2 = crossPattern
    int winStepIter{1};
    std::pair<int, int> positionMap;
    std::array<std::array<int, 3>, 3> implementationMap{};
    std::vector<std::string> crossPattern{
        {"   ***   "},
        {"  *   *  "},
        {" *     * "},
        {"  *   *  "},
        {"   ***   "}
    };

    std::vector<std::string> zeroPattern{
        {"  *   *  "},
        {"   * *   "},
        {"    *    "},
        {"   * *   "},
        {"  *   *  "}
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
