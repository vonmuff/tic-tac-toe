cmake_minimum_required(VERSION 3.16)

add_executable(tictachoe main.cpp)
target_link_libraries(tictachoe GameLib)
target_compile_features(tictachoe PUBLIC cxx_std_20)