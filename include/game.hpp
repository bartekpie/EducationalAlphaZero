#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <concepts>

/**
 * Abstract interface for search algorithm (MCTS).
 * Object do not change only produce changed copy.
 * 
 */
enum class Player {
    player1, 
    player2,
    None
};
enum class Status {
    draw, 
    player1Win,
    player2Win,
    notTerminal
};
/**
 * Abstract interface for search algorithm (MCTS).
 * Object do not change only produce changed copy.
 * 
 */
template<typename G>
concept Game = 
requires(const G g, int move) {
    { g.getLegalMoves() } -> std::convertible_to<std::vector<int>>;
    { g.applyMove(move) } -> std::convertible_to<G>;
    { g.isTerminal() } -> std::convertible_to<bool>;
    { g.checkGameStatus() } -> std::convertible_to<Status>;
    { g.getCurrPlayer() } -> std::convertible_to<Player>;
};

