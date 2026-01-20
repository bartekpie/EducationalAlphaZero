cmake_minimum_required(VERSION 3.1)

project(Net)

set(CMAKE_PREFIX_PATH "C:\Users\barte\dynamic_lib\libtorch-win-shared-with-deps-latest\libtorch\share\cmake\Torch")

find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(main src/main.cpp src/network.cpp src/game.cpp src/mcts.cpp src/TicTacToe.cpp include/game.hpp include/TicTacToe.hpp include/network.hpp)
target_include_directories(main PRIVATE include)

target_link_libraries(main ${TORCH_LIBRARIES})

set_property(TARGET main PROPERTY CXX_STANDARD 17)