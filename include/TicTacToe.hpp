#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include "game.hpp"

namespace TicTacToe {
  

  using State = std::array<std::array<Player, 3>, 3>;
  
  class Ttt {
    public:
      Ttt();
      gameState getState()const;
      void gameLoop();
      std::vector<int> getLegalMoves()const ;
      std::unique_ptr<TicTacToe> applyMove(int move)const ;
      Player checkGameStatus()const;
      bool isTerminal()const ;
      Player getCurrPlayer()const;
    private:
      State state_ ;
      Player currPlayer_{ Player::Player1 };
      // for a visualisation and game order
      // not used in AlphaZero framework 
      void muteState(int move);
      void visualizeBoard()const;
      int getMove()const;
      bool processMove(int move);
      bool checkStateAfterMove() const;
  };
}
