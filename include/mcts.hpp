#include "game.hpp"
#include "network.hpp"
#include <iostream>
#include <memory>
#include <vector>

template<Game G>
class Node {
  public:
   template<typename T>
   friend class Mcts;
    Node(G game, Node* parent=nullptr, int actionTaken = -1) : 
      state_(game),
      actionTaken_(actionTaken),
      parent_(parent) {}
  private:
    std::vector<std::unique_ptr<Node<G>>> children_;
    Node* parent_;
    G state_;
    int vistCount_;
    int value_;

}
//purpose of this class is to simulate monte-carlo tree search
//with
template<Game G>
class Mcts {
  public: 
    friend class AlphaZero;
    Mcts();
    Mcts(Node<G>* root, NeuralNetwork net) : net_(net) {};
    run();

    
  private:
    Node<G>* root_;
    NeuralNetwork& net_;
    double uct(double policy);
    Node* select(Node* node);
    Node* expand(Node* node);
    backpropagate();
    iterationMcts();
    

}