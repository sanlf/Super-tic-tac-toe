#ifndef PLAYER_H
#define PLAYER_H

#include <string> //for string

#include "Enumerations.h" //for Type and Position enumerations
#include "Colors.h" //for struct Colors
#include "BigBoard.h" //for BigBoard

/**
    \brief Class Player of tic-tac-toe. The player has a name and a piece. 
    \author Sotomayor Samaniego Luis Fernando.
    \date 2017/05/28
    \version 1.0
*/

class Player
{
    public:

        /**
            \brief Constructor of a player. By default the name is an empty string and the piece is 'a'.
            \param piece Piece the player would like to play with.
            \param name Name of the player.
        */
        Player(std::string name, std::string piece, Type type, const BigBoard& board, ALLEGRO_COLOR color);

        /**
            \brief Method to get the piece of the player.
            \return Piece of the player.
        */
        std::string getPiece() const { return m_piece; }

        /**
            \brief Method to get the player's name.
            \return Name of the player.
        */
        std::string getName() const { return m_name; }

        ALLEGRO_COLOR getColor() const { return m_color; }

        Type getType() const { return m_type; }

        /**
            \brief Method to set the piece of the player.
            \param newPiece new piece the player should have.
        */
        void setPiece(std::string newPiece) { m_piece = newPiece; }

        /**
            \brief Method to set the name of the player.
            \param newName new name the player should have.
        */
        void setName(std::string newName) { m_name = newName; }

    private:
        std::string m_name;
        std::string m_piece;
        Type m_type;
        const BigBoard& m_board;
        ALLEGRO_COLOR m_color;
};

#endif // PLAYER_H
