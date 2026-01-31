#include"TicTacToe.hpp"
#include "mcts.hpp"
#include "network.hpp"
#include <iostream>

int main() {
  NeuralNetwork net(10, 2, 10000, 0.2);
  Mcts<TicTacToe::Ttt> mcts(net);
  mcts.run(100);
  
}