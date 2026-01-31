#pragma once
#include "game.hpp"
#include "network.hpp"
#include <iostream>
#include <memory>
#include <vector>

// helper template class to structure the node of personalizetd MCTS 

template<Game G>
class Node {
  public:
    template<typename T> friend class Mcts;
    Node(G game, Node* parent=nullptr, int actionTaken = -1) : 
      state_(game),
      parent_(parent),
      value_(0.0),
      prior_(0.0),
      visitCount_(0) {}
  private:
    std::vector<std::unique_ptr<Node<G>>> children_;
    Node* parent_;
    G state_;
    int visitCount_;
    double value_;
    double prior_;


};

//purpose of this class is to simulate monte-carlo tree search
//chenged to be compatible with alpha zero uct -> puct , no rnadom simualtion using nn instead

template<Game G>
class Mcts {
  public: 
    Mcts(Node<G>* root = nullptr, NeuralNetwork& net) : 
      net_(net),
      root_(root),
      procentOfKnowledge_(0.0) {};

    void run(int num); 

  private:
    int currBackProp_{0};
    int termBackProp_{0};
    double procentOfKnowledge_;
    Node<G>* root_;
    NeuralNetwork& net_;
    double uct();
    Node* select(Node<G>* node);
    Node* expand(Node<G>* node);
    void backpropagade(Node<G>* node, Status status);
    void backpropagade(Node<G>* node, double value);
    void iteration();
};