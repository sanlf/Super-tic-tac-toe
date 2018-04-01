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

