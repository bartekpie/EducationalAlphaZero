cmake_minimum_required(VERSION 3.6)

project(main)

set(CMAKE_PREFIX_PATH "C:/Users/barte/dynamic_lib/libtorch-win-shared-with-deps-latest/libtorch/share/cmake/Torch")

find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(main src/main.cpp src/network.cpp src/mcts.cpp src/TicTacToe.cpp include/game.hpp include/mcts.hpp include/TicTacToe.hpp include/network.hpp)
target_include_directories(main PRIVATE include)

target_link_libraries(main ${TORCH_LIBRARIES})

set_property(TARGET main PROPERTY CXX_STANDARD 20)
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET main
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:main>)
endif (MSVC)