//
// Created by user on 11.12.2025.
//

#ifndef TICTACHOE_GAME_H
#define TICTACHOE_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
class Game {
    public:
        void welcome();
        void render() const;
        void step();
    private:
    std::pair<int,int> positionMap;
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
