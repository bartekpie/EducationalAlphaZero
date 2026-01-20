#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include "game.hpp"

namespace TicTacToe {
  

  using gameState = std::array<std::array<Player, 3>, 3>;
  
  class Ttt : public Game {
    public:
      Ttt();
      gameState getState()const;
      void gameLoop();
      std::vector<int> getLegalMoves()const override;
      std::unique_ptr<Game> applyMove(int move)const override;
      bool checkWinner()const override;
      bool isTerminal()const override;
    private:
      gameState state_ ;
      //Player currPlayer_{ Player::Cross };
      void muteState(int move);
      void visualizeBoard()const;
      int getMove()const;
      bool processMove(int move);
      bool checkStateAfterMove() const;

  };
}
