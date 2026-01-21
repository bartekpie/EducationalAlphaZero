#ifndef GAME
#define GAME
#include <iostream>
#include <vector>
#include <memory>
#include <concept>

/**
 * Abstract interface for search algorithm (MCTS).
 * Object do not change only produce changed copy.
 * 
 */
enum class Player {
    player1, 
    player2,
    None
}
enum class Status {
    draw, 
    player1Win,
    player2Win,
    notTerminal
}
/**
 * Abstract interface for search algorithm (MCTS).
 * Object do not change only produce changed copy.
 * 
 */
template<typename G>
concept Game = 
requires(const G g, int move) {
    { g.getLegalMoves() } -> std::same_as<std::vector<int>>;
    { g.applyMove(move) } -> std::same_as<G>;
    { g.isTerminal() } -> std::same_as<bool>;
    { g.checkGameStatus() } -> std::same_as<Status>;
    { g.getCurrPlayer() } -> std::same_as<Player>;
}

#endif