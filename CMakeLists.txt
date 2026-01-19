cmake_minimum_required(VERSION 3.1)

project(Net)

set(CMAKE_PREFIX_PATH /home/vboxuser/Downloads/libtorch-shared-with-deps-2.9.1+cpu/libtorch/share/cmake)

find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(main src/main.cpp src/network.cpp src/game.cpp src/mcts.cpp include/mcts.hpp include/game.hpp include/TicTacToe.hpp include/network.hpp)
target_include_directories(main PRIVATE include)

target_link_libraries(main ${TORCH_LIBRARIES})

set_property(TARGET main PROPERTY CXX_STANDARD 17)