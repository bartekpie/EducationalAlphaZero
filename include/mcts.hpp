#include "game.hpp"
#include "network.hpp"
#include <iostream>
#include <memory>
#include <vector>

template<Game G>
class Node {
  public:
   friend class Mcts;
    Node(G game, Node* parent=nullptr, int actionTaken = -1) : 
      state_(game),
      actionTaken_(actionTaken),
      parent_(parent) {}
  private:
    std::vector<std::unique_ptr<Node>> children_;
    G state_;
    int actionTaken_;

}
//purpose of this class is to simulate monte-carlo tree search
//with
template<Game G>
class Mcts {
  public: 
    Mcts();
    Mcts(Node<G>* root, NeuralNetwork* net );
    run();
    exportData();
    
  private:
    Node<G>* root_;
    NeuralNetwork* net_;
    uct();
    select();
    expand();
    getPolicy();
    backpropagate();
    iterationMcts();
    

}