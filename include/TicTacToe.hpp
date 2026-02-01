#include "game.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <array>


namespace TicTacToe{
  

  using State = std::array<std::array<Player, 3>, 3>;
  
  class Ttt {
    public:
      Ttt();
      Ttt(State s, Player p): state_(s), currPlayer_(p){}
      State getState() const ;
      void gameLoop();
      std::vector<int> getLegalMoves()const ;
      Ttt applyMove(int move)const ;
      Status checkGameStatus()const;
      bool isTerminal()const ;
      Player getCurrPlayer()const;
    private:
      State state_ ;
      Player currPlayer_;
      // for a visualisation and game order
      // not used in AlphaZero framework 
      void muteState(int move);
      void visualizeBoard()const;
      int getMove()const;
      bool processMove(int move);
      bool checkStateAfterMove() const;
  };
};
