#include "../include/Player.h"

/**************************************************************************************************/
Player::Player(std::string name,
               std::string piece,
               Type type,
               const BigBoard& board,
               ALLEGRO_COLOR color  ):m_name(name),
                                      m_piece(piece),
                                      m_type(type),
                                      m_board(board),
                                      m_color(color)
{}
/**************************************************************************************************/
std::pair<Position, Position> Player::agentDecision(Position currpos)
{
    //this only should work when the player is an AI
    if(m_type != Type::AI)
         return std::pair<Position,Position>(Position::NONE, Position::NONE);

    auto legalplays = legalPlays(m_board, currpos);

    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<int> dist(0, legalplays.size() - 1);

    return legalplays[dist(engine)];
}

/**************************************************************************************************/
/*NON CLASS CODE*************************************************************************************************/
/**************************************************************************************************/
//board is a big board of tictactoe and currpos is the position of the current selected board.
//
//returns a vector of pairs with all the posible plays. The first part is the position of the board
//and the second is the position of the cell
std::vector< std::pair<Position, Position> > legalPlays(const BigBoard& board, Position currpos)
{
    std::vector< std::pair<Position, Position> > plays;
    if(currpos != Position::NONE){
        if(board[currpos].getWinner() == NO_WINNER)
            for(int i = 0; i < 9; ++i)
                if(board[currpos][i].piece == EMPTY)
                    plays.push_back(std::pair<Position, Position>(currpos,
                                                                  static_cast<Position>(i)));

    }else{ //if(currpos == Position::NONE){
        for(int i = 0; i < 9; ++i){
            if(board[i].getWinner() == NO_WINNER)
                for(int j = 0; j < 9; ++j)
                    if(board[i][j].piece == EMPTY)
                        plays.push_back(std::pair<Position, Position>(static_cast<Position>(i),
                                                                      static_cast<Position>(j)));
        }
    }

    return plays;
}

