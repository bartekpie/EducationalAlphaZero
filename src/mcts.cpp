#include "mcts.hpp"

double Mcts::uct(double policy) {
    if (child -> visitcount == 0) 
      return std::numeric_limits<double>::infinity();
    return (child->value / child->visitcount) + policy * std::sqrt(std::log(parent->visitcount) / child->visitcount);
}
Node* Mcts::select(Node* node) {
    while (node->state_.isTerminal()) {
        if (node->children.size() < node->state_.getLegalMoves().size()) {
            return node;
        }
        double best{-1e9};
        Node* bestNode = nullptr;
        for (const auto& child : node->children) {
          auto curr = uct(child, net(child->state_));
          if (curr>best) {
            best = curr;
            bestNode = child;
          }

        }
        node = bestNode;
    }
    return node;
}
Node* Mcts::expand(Node* node) {
    const auto& moves = node->state_.getLegalMoves();
    if (node->children.size() < moves.size()) {
        auto move = moves[node->children.size()];
        auto game = node->state_.applyMove(move);
        node.children.push_back(std::make_unique<Node<G>>(game, node, move);
        return node->children.back().get();
     )
    } else {
        /// think how to handle that ; // add node counter to see how much procent of poossibiliteis the game is expanded 
    }
}
void Mcts::mctsiteration(Node* root) {
    Node* node = select(root);
    if (!isTerminal(node->gamestate))
      node = expand(node);
    int winner = simulate(node->gamestate);
    backpropagate(node, winner);
}