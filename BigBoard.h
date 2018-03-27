#ifndef BIGBOARD_H
#define BIGBOARD_H

#include<memory> // for shared_ptr
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <string>
#include "BoardInterface.h" //for Board interface
#include "SmallBoard.h" //for SmallBoard class
#include "../Positions.h" //for POSITION enumeration
#include "Redefinitions.h" //for DisplayPtr
#include "../Window.h"
#include "../AllegroColors.h"

#define NUM_SMALL_BOARDS 9

/**
    \brief Class board which has smaller boards in it.
    \author Sotomayor Samaniego Luis Fernando.
    \date 2017/05/28
    \version 1.0
*/

class TicTacToe;

/**
    \brief Class BigBoard which has a SmallBoard of Tic-Tac-Toe in each of its cells.
    \author Sotomayor Samaniego Luis Fernando.
    \date 2017/06/02
    \version 1.0
*/

class BigBoard : Board
{
public:

    friend TicTacToe;

    /**
        \brief Method to reset the atributes of the board so it becomes like a new one.
    */
    void reset();

    /**
        \brief Method to put a piece in the board.
        \pre The position where the piece is going to be put must be empty.
        \param piece Piece to put in the board.
        \param smallBoard small board where you want to put a piece.
        \param position Position where the piece is going to be putted in a small board.
        \return True if the position was empty and the piece was put, false otherwise.
    */
    bool putPiece(std::string piece, SmallBoard& smallBoard, Position position);

    /**
        \brief Method to get an instance of BigBoard. This allways returns the same object.
        \param display Display where the game is going to be output.
        \param window Size of window and screen.
        \return A reference to a BigBoard.
    */
    static BigBoard& getInstance(DisplayPtr display, const Window& window){
        static BigBoard instance(display, window);

        return instance;
    }

    /**
        \brief Method to check if there is a winner or a tie in the board.
        \return the piece of the winner. Empty if there is still no winner and 't' if tied.
    */
    std::string checkWinner() const { return m_winner; }

    /**
        \brief Method to draw the whole board.
        \param font Font to use to draw the elements of the board.
    */
    void draw(FontPtr font) const;

    /**
        \brief Overload of the operator []. This will get you the small board in the received position.
        \param position Position of the small board you want.
        \return Small board in the received position.
    */
    SmallBoard& operator[](Position position) { return m_smallBoard[position]; }

    /**
        \brief Overload of the const operator []. This will get you the small board in the received position.
        \param position Position of the small board you want.
        \return Small board in the received position.
    */
    const SmallBoard& operator[](Position position) const { return m_smallBoard[position]; }

    /// These two are deleted so there can not exists copies of the BigBoard
    BigBoard(const BigBoard& ) = delete;
    void operator=(const BigBoard& ) = delete;

private:
    std::vector<SmallBoard> m_smallBoard;
    std::string m_winner;
    DisplayPtr m_display;
    Window m_size;

    /**
        \brief Constructor of the BigBoard. This is a singleton class so you can't construct objects of it.
        \param display Display of the game where the board is going to be drawed in.
        \param window Size of window and screen.
    */
    BigBoard(DisplayPtr display, const Window& window);

    /**
        \brief Method to check if the game ended and there is a winner or tie and updates the winner
                accordingly.
    */
    void checkIfGameEnded();
};

#endif // BIGBOARD_H
