#include "TicTacToe.hpp"
namespace Ttt {
  Ttt::Ttt() {
    for (auto& column : state_)
      column.fill(Player::None);

  }
  gameState&& Ttt::getState() const{
    return state_;
  }
  std::vector<int> getLegalMoves()const override {
    std::vector<int> moves;
    for (auto i{}; i < 3; i++) {
      for (auto j{}; j < 3; j++) {
        if (state_[i] == Player::None)
          moves.push_back(i*3 + j);
      }
    }
    return moves ;
  }
  std::unique_ptr<Game> Ttt:: applyMove(int move)const override {
    unique_ptr<Game> newState = std::make_unique<Ttt>(*this);
    int row = move / 3;
    int col = move % 3;
    newState -> state_[row][col] = newState -> currPlayer_;
    newState -> currPlayer_ = (newState -> currPlayer_ == Player::Cross) ? Player::Circle : Player::Cross;
    return std::move(newState);
  }
  int Ttt::checkWinner()const override {
    //rows
     for (auto i{}; i < 3; ++i) {
        if (state_[i][0] == Player::None) continue;
        if (state_[i][1] != state[i][0]) continue;
        if (state_[i][2] == state_[i][1]) 
            return static_cast<int>(state[i][0]);
    
     }
     //columns
     for (auto i{}; i < 3; ++i) {
        if (state_[0][i] == Player::None) continue;
        if (state_[1][i] != state[0][i]) continue;
        if (state_[2][i] == state_[1][i]) 
          return static_cast<int>(state_[i][0]);
    
     }
     if (state_[0][0] != Player::None && state_[1][1] == state_[0][0] && state_[2][2] == state_[1][1])
       return static_cast<int>(state_[0][0]);
     if (state_[0][2] != Player::None && state_[1][1] == state_[0][2] && state_[2][0] == state_[1][1])
       return static_cast<int>(state_[0][0]);
   }
   bool Ttt::isTerminal()const override {
      if (checkWinner() == true)
        return true;
      for (auto i{}; i < 3; i++) {
        for (auto j{}; j < 3; j++) {
          if (state_[i][j] == Player::None)
            return false;
        }
      }
      return true;
   }
  }

};


