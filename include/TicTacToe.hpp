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
      Ttt()
      gameState&& getState()const;
    private:
      gameState state_ ;
      Player currPlayer_{ Player::Cross };
  };
}
