#pragma once
#include "game.hpp"
#include "network.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include <cmath>

// helper template class to structure the node of personalizetd MCTS 

template<Game G>
class Node {
  public:
    template<Game> friend class Mcts;
    Node(G game = G(), Node* parent=nullptr, int actionTaken = -1) : 
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
    Mcts(NeuralNetwork& net, ) : 
      net_(net),
      root_(std::make_unique<Node<G>>()),
      procentOfKnowledge_(0.0) {}

    void run(int num); 

  private:
    int currBackProp_{0};
    int termBackProp_{0};
    float procentOfKnowledge_;
    std::unique_ptr<Node<G>> root_;
    NeuralNetwork& net_;
    double puct(Node<G>* child);
    Node<G>* select(Node<G>* node);
    Node<G>* expand(Node<G>* node);
    void backpropagade(Node<G>* node, Status status);
    void backpropagade(Node<G>* node, double value);
    void iteration();
};