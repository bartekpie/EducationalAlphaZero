#include"TicTacToe.hpp"
#include "mcts.hpp"
#include <iostream>

int main() {
  TicTacToe::Ttt game());
  NeuralNetwork net(10, 2, 10000, 0.2);
  Mcts<TicTacToe::Ttt> mcts(net);
  mcts.run(100);
  
}