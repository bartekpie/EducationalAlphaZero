#include "mcts.hpp"
#include <cassert>

template<Game G>
double Mcts::uct(Node<G>* child) {
    if (child -> visitcount == 0) 
      return std::numeric_limits<double>::infinity();
    return ( child->value_ / child->visitCount_ ) + child->prior_ * std::sqrt(std::log(child->parent_->visitcount_) / child->visitcount_);
}
template<Game G>
Node<G>* Mcts::select(Node<G>* node) {
    while (node->state_.isTerminal() == false) {
        if (node->children.size() < node->state_.getLegalMoves().size()) {
            return node;
        }
        double best{-1e9};
        Node<G>* bestNode = nullptr;
        for (const auto& child : node->children) {
          auto curr = uct(child);
          if (curr>best) {
            best = curr;
            bestNode = child;
          }
        }
        node = bestNode;
    }
    return node;
}
template<Game G>
Node<G>* Mcts::expand(Node<G>* node) {
    const auto& moves = node->state_.getLegalMoves();
    std::assert(node->children.size() < moves.size());
    auto move = moves[node->children.size()];
    auto game = node->state_.applyMove(move);
    node->children.push_back(std::make_unique<Node<G>>(game, node, move));
    return node->children.back().get();
    
    
}
template<Game G>
void Mcts::backpropagade(Node<G>* node, Status status) {
    while (node->parent != nullptr) {
       node->visitCount_++;
       if(status == Status::player1Win)
        node->value_ += (node->state_.getCurrentPlayer() == Player::player1) ? 1 : -1;
       if(status == Status::player2Win)
        node->value_ += (node->state_.getCurrentPlayer() == Player::player2) ? 1 : -1;
       node = node->parent_;
    }
} 
template<Game G>
void Mcts::backpropagade(Node<G>* node, double value) {
    while (node->parent != nullptr) {
       node->visitCount_++;
       node->value_ += value;
       value = -value;
       node = node->parent_;
    }
}  
template<Game G>      
void Mcts::iteration() {
    Node<G>* node = root_;
    node = select(node);
    if (isTerminal(node->state_)) {
      backpropagate(node, node->state_.getGameStatus());
      termBackProp++;
    } else {
       node = expand(node);
       auto [policy, value] = net_.forward(node->state_);
       node->prior = policy;
       backpropagate(node, value);
    }
}
template<Game G>
void Mcts::run(int num) {
  for (auto i{0}; i < num; i++){
    iteration();
    currBackProp++;
    procentOfKnowledge_ = (termBackProp / currBackProp);
  }
}