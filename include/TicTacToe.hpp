#include "game.hpp"
#include <array>
namespace TicTacToe {
  enum class Player{
    None, 
    Cross,
    Circle
  };

  using gameState = std::array<std::array<Player, 3>>;
  
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
      Player currPlayer_{ Player::Cross };
      void muteState(int move);
      void visualizeBoard()const;
      void getMove()const;
      bool processMove(int move);
      bool checkStateAfterMove() const;

  };
}
