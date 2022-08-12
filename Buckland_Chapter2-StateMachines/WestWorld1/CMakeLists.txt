cmake_minimum_required(VERSION 3.13)
project(westworld CXX)

include_directories(include ../../Common)
add_executable(sample src/main.cpp src/Miner.cpp src/MinerOwnedStates.cpp src/BaseGameEntity.cpp)
