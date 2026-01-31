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
      visitCount_(0) {};
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
class Mcts{
  public: 
    Mcts(NeuralNetwork& net) : 
      net_(net),
      root_(std::make_unique<Node<G>>()),
      procentOfKnowledge_(0.0) {};

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
template<Game G>
double Mcts<G>::puct(Node<G>* child) {
    if (child->visitCount_ == 0)
        return std::numeric_limits<double>::infinity();
    return (child->value_ / child->visitCount_) + child->prior_ * std::sqrt(std::log(child->parent_->visitcount_) / child->visitcount_);
}
template<Game G>
Node<G>* Mcts<G>::select(Node<G>* node) {
    while (node->state_.isTerminal() == false) {
        if (node->children_.size() < node->state_.getLegalMoves().size()) {
            return node;
        }
        double best{ -1e9 };
        Node<G>* bestNode = nullptr;
        for (const auto& child : node->children_) {
            auto curr = puct(child);
            if (curr > best) {
                best = curr;
                bestNode = child;
            }
        }
        node = bestNode;
    }
    return node;
}
template<Game G>
Node<G>* Mcts<G>::expand(Node<G>* node) {
    const auto& moves = node->state_.getLegalMoves();
    auto move = moves[node->children_.size()];
    G game = node->state_.applyMove(move);
    node->children_.push_back(std::make_unique<Node<G>>(game, node, move));
    return node->children_.back().get();


}
template<Game G>
void Mcts<G>::backpropagade(Node<G>* node, Status status) {
    while (node != nullptr) {
        node->visitCount_++;
        if (status == Status::player1Win)
            node->value_ += (node->state_.getCurrPlayer() == Player::player1) ? 1 : -1;
        if (status == Status::player2Win)
            node->value_ += (node->state_.getCurrPlayer() == Player::player2) ? 1 : -1;
        node = node->parent_;
    }
}
template<Game G>
void Mcts<G>::backpropagade(Node<G>* node, double value) {
    while (node != nullptr) {
        node->visitCount_++;
        node->value_ += value;
        value = -value;
        node = node->parent_;
    }
}
template<Game G>
void Mcts<G>::iteration() {
    Node<G>* node = root_.get();
    node = select(node);
    if (node->state_.isTerminal()) {
        backpropagade(node, node->state_.checkGameStatus());
        termBackProp_++;
    }
    else {
        node = expand(node);
        auto [policy, value] = TensorToPair(net_.forward(vector<int>(node->state_.begin(), node->state_.end()));
        node->prior_ = policy;
        backpropagade(node, value);
    }
}
template<Game G>
void Mcts<G>::run(int num) {
    for (auto i{ 0 }; i < num; i++) {
        iteration();
        currBackProp_++;
        procentOfKnowledge_ = (termBackProp_ / currBackProp_);
    }
}
