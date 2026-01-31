#include "TicTacToe.hpp"
namespace TicTacToe {
  using State = std::array<std::array<Player, 3>, 3>;
  Ttt::Ttt() {
    for (auto& column : state_)
      column.fill(Player::None);
    currPlayer_ = Player::player1;
  }
  State Ttt::getState()const {
    return state_;
  }
  Player Ttt::getCurrPlayer()const {
    return currPlayer_;
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
    
  Ttt Ttt::applyMove(int move)const  {
    int row = move / 3;
    int col = move % 3;
    State newstate = state_;
    newstate[row][col] = currPlayer_;
    Player p = ( currPlayer_ == Player::player1) ? Player::player2 : Player::player1;
    return Ttt a(newstate, p);
  }
  Status Ttt::checkGameStatus()const {
    //rows
     for (auto i{0}; i < 3; ++i) {
        if (state_[i][0] == Player::None) continue;
        if (state_[i][1] != state_[i][0]) continue;
        if (state_[i][2] == state_[i][1]) 
            return ((currPlayer_ == Player::player1) ? Status::player1Win : Status::player2Win );
     }
     //columns
     for (auto i{0}; i < 3; ++i) {
        if (state_[0][i] == Player::None) continue;
        if (state_[1][i] != state_[0][i]) continue;
        if (state_[2][i] == state_[1][i]) 
          return ((currPlayer_==Player::player1) ? Status::player1Win : Status::player2Win );    
     }
     if (state_[0][0] != Player::None && state_[1][1] == state_[0][0] && state_[2][2] == state_[1][1])
       return ((currPlayer_==Player::player1) ? Status::player1Win : Status::player2Win ); 
     if (state_[0][2] != Player::None && state_[1][1] == state_[0][2] && state_[2][0] == state_[1][1])
       return ((currPlayer_==Player::player1) ? Status::player1Win : Status::player2Win ); 
     // check for 
     for (auto i{0}; i < 3; i++) {
        for (auto j{0}; j < 3; j++) {
          if (state_[i][j] == Player::None)
            return Status::notTerminal;
        }
      }
      return Status::draw;
   }
   bool Ttt::isTerminal()const {
      if (checkGameStatus() == Status::notTerminal)
        return false;
      return true;
   }
  void Ttt::visualizeBoard()const {
    std::cout<<std::endl;
    for (const auto& row : state_) {
      for (const auto& num : row) {
        if (num == Player::player2)
          std::cout << "O";
        else if (num == Player::player1)
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
    switch(checkGameStatus()){
      case Status::player1Win :
        std::cout<< "Cross wins";
        return true;
      case Status::player2Win : 
        std::cout<< "Circle wins";
        return true;
      case Status::draw : 
        std::cout<< "Draw";
        return true;
      default : 
        return false;
    }
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
    currPlayer_ = (currPlayer_ == Player::player1) ? Player::player2 : Player::player1;
  }
};


