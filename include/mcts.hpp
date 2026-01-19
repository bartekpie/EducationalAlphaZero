#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <cmath>
#include <cstdlib>
#include "game.hpp"
namespace MCTS {
struct Node {
  Node * parent;
  std::vector<std::unique_ptr<Node>> children;
  int visitcount{0};
  int value{0};
  int move;
  std::unique_ptr<Game> gamestate;
  Node(Node * parent = nullptr, std::unique_ptr<Game> gamestate, int move = -1) : 
    parent(parent),
    gamestate(gamestate),
    move(move),
    visitcount(0) {}

};

double uct(const Node* parent, const Node* child) {
    if (child -> visitcount == 0) 
      return std::numeric_limits<double>::infinity();
    return (child->value / child->visitcount) + 2 * std::sqrt(std::log(parent->visitcount) / child->visitcount);
}
Node* select(Node* node) {
    while (node->gamestate->isTerminal() == false) {
        auto moves = node->gamestate->getLegalMoves();
        if (node->children.size() < moves.size()) {
            return node;
        }
        Node * bestNode = nullptr;
        double best{-1e9};
        for (auto& a : node->children) {
            auto current = uct(node, a.get());
            if (current > best) {
              best = current;
              bestNode = a.get();
            }
        }
        node = bestNode;
    }
    return node;
}

std::unique_ptr<Node> expand(Node* node) {
    auto moves = node -> gamestate -> getLegalMoves() ;
    int move =  moves[node->children.size()];
    GameState next = applyMove(node->gamestate, move);

    node->children.push_back(std::make_unique<Node>(node, next, move));
    return node->children.back().get();
}

int simulate(std::unique_ptr<Game> s) {
    while (s->isTerminal() == false) {
      auto moves = s->getLegalMoves();
      int move = moves[rand() % moves.size()];
      s = s->applyMove(move);
    }
    return s->checkWinner();
}

void backpropagate(Node* node, int winner) {
  while (node->parent != nullptr) {
    node->visitcount++;
    if (winner != 0) {
        if (winner = node->gamestate.currentplayer) {
            node->value -= 1;
        } else {
            node->value += 1;
        }
    }
    node = node->parent;
  }
}

void mctsiteration(Node* root) {
    Node* node = select(root);
    if (node->gamestate->isTerminal() == false)
      node = expand(node);
    int winner = simulate(node->gamestate);
    backpropagate(node, winner);
}

void runMCTS(Node*root, int numofsimulations) {
  for (auto a{}; a < numofsimulations; a++)
    mctsiteration(root);
}
}
