cmake_minimum_required(VERSION 3.16)

add_library(GameLib source/Game.cpp)
target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(GameLib PUBLIC cxx_std_20)