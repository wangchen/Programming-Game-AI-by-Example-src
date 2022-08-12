cmake_minimum_required(VERSION 3.13)
add_compile_options(-std=c++14)
project(westworld_with_woman CXX)

include_directories(include ../../Common)
add_executable(sample src/main.cpp src/Miner.cpp src/MinerOwnedStates.cpp src/MinersWife.cpp src/MinersWifeOwnedStates.cpp src/BaseGameEntity.cpp)
