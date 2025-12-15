cmake_minimum_required(VERSION 3.16)

add_executable(tictactoe main.cpp)
target_link_libraries(tictactoe GameLib)
target_compile_features(tictactoe PUBLIC cxx_std_20)