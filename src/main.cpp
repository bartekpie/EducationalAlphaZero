#include"TicTacToe.hpp"
#include "mcts.hpp"
#include <iostream>

int main() {
  TicTacToe::Ttt game());
  NeuralNetwork net(t.getStateSize(), 2, 100, 0.2);
  Mcts mcts(new node<TicTacToe::Ttt>(game), net);
  for (auto a{0}; a < 100; a++) {
    mcts.run(100);
    auto dataToLearn = exportToTrain(mcts);
    net.train(dataToLearn);
  }
}