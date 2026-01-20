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
class Game {
public:
    virtual ~Game() = default;
    virtual std::vector<int> getLegalMoves()const = 0;
    virtual std::unique_ptr<Game> applyMove(int move)const = 0;
    virtual bool checkWinner()const = 0;
    virtual bool isTerminal()const = 0;
protected :
  Player currPlayer_;

};

#endif