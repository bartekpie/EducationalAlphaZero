
#include <iostream>
#include <vector>
#include <memory>
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
    virtual int checkWinner()const = 0;
    virtual bool isTerminal()const = 0;

};


