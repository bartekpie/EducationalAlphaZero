#include "TicTacToe.hpp"
namespace TicTacToe {
  using gameState = std::array<std::array<Player, 3>, 3>;
  Ttt::Ttt() {
    for (auto& column : state_)
      column.fill(Player::None);
    currPlayer_ = Player::Cross;
  }
  gameState Ttt::getState() const{
    return state_;
  }
  std::vector<int> Ttt::getLegalMoves()const {
    std::vector<int> moves;
    for (auto i{0}; i < 3; i++) {
      for (auto j{0}; j < 3; j++) {
        if (state_[i][j] == Player::None)
          moves.push_back(i*3 + j);
      }
    }
    return moves ;
    }
    
  std::unique_ptr<Game<gameState>> Ttt::applyMove(int move)const  {
    int row = move / 3;
    int col = move % 3;
    gameState newstate = state_;
    newstate[row][col] = currPlayer_;
    Player p = ( currPlayer_ == Player::Cross) ? Player::Circle : Player::Cross;
    return std::make_unique<Game<gameState>>(newstate, p);
  }
  bool Ttt::checkWinner()const {
    //rows
     for (auto i{0}; i < 3; ++i) {
        if (state_[i][0] == Player::None) continue;
        if (state_[i][1] != state_[i][0]) continue;
        if (state_[i][2] == state_[i][1]) 
            return true;
    
     }
     //columns
     for (auto i{0}; i < 3; ++i) {
        if (state_[0][i] == Player::None) continue;
        if (state_[1][i] != state_[0][i]) continue;
        if (state_[2][i] == state_[1][i]) 
          return true;    
     }
     if (state_[0][0] != Player::None && state_[1][1] == state_[0][0] && state_[2][2] == state_[1][1])
       return true; 
     if (state_[0][2] != Player::None && state_[1][1] == state_[0][2] && state_[2][0] == state_[1][1])
       return true; 
     return false;
   }
   bool Ttt::isTerminal()const {
      if (checkWinner() == true)
        return true;
      for (auto i{0}; i < 3; i++) {
        for (auto j{0}; j < 3; j++) {
          if (state_[i][j] == Player::None)
            return false;
        }
      }
      return true;
   }
  void Ttt::visualizeBoard()const {
    std::cout<<std::endl;
    for (const auto& row : state_) {
      for (const auto& num : row) {
        if (num == Player::Circle)
          std::cout << "O";
        else if (num == Player::Cross)
          std::cout << "X"; 
        else {
            std::cout<< " ";
        }
      }
      std::cout<<std::endl;
    }
    std::cout<<std::endl;
  }
  int Ttt::getMove()const {
    int x{};
    int y{};
    std::cout << "give x cordinate ::" ;
    std::cin >> x;
    std::cout << "give y cordinate ::" ;
    std::cin >> y;
    return (y * 3 + x);
  }
  bool Ttt::processMove (int move) {
    for (const auto& v : getLegalMoves()) {
      if (v == move) {
        muteState(move);
        return true;
      }
    }
    std::cout<< "niepoprawny ruch" <<std ::endl;
    return false;
      
        
  }
  bool Ttt::checkStateAfterMove()const {
    if(isTerminal()){
      if(checkWinner()) {
        std::cout<< "Winner ::"<< ((currPlayer_ == Player::Cross) ? "Circle" : "Cross");
      } else {
        std::cout<<"Draw";
      }
      return true;
     }
     return false;
  }
  void Ttt:: gameLoop() {
    while (true) {
        visualizeBoard();
        if (processMove(getMove())){
          if (checkStateAfterMove())
            break;
        } 
           
    }
  }
  void Ttt::muteState(int move) {
    int row = move / 3;
    int col = move % 3;
    state_[row][col] = currPlayer_;
    currPlayer_ = (currPlayer_ == Player::Cross) ? Player::Circle : Player::Cross;
  }
};


