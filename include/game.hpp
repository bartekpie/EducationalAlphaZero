#ifndef GAME
#define GAME
#include <iostream>
#include <vector>
#include <memory>
enum class Player{
    None, 
    Cross,
    Circle
};
/**
 * Abstract interface for search algorithm (MCTS).
 * Object do not change only produce changed copy.
 * 
 */
template<typename State>
class Game {
public:
    Game(State s, Player p): currPlayer_(p), state_(s){};
    virtual ~Game() = default;
    virtual std::vector<int> getLegalMoves()const = 0;
    virtual std::unique_ptr<Game<State>> applyMove(int move)const = 0;
    virtual bool checkWinner()const = 0;
    virtual bool isTerminal()const = 0;
protected :
  Player currPlayer_;
  State state_;

};

#endif