#ifndef BIGBOARD_H
#define BIGBOARD_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <string> //for std::string
#include <array> //for std::array
#include <algorithm> //for std::all_of
#include <math.h> //for fabs
#include <allegro5/allegro_font.h> //for allegro font

#include "SmallBoard.h" //for SmallBoard class
#include "Point.h" //for Point struct
#include "Colors.h" //for colors global variable
#include "Enumerations.h" //for enumerations of Positions
#include "Constants.h" //for NO_WINNER, LINE_THICKNESS

extern Colors COLOR;

/*
    \brief Class BigBoard which has a SmallBoard of Tic-Tac-Toe in each of its cells.
    \author Sotomayor Samaniego Luis Fernando.
    \date 2017/06/02
    \version 1.0
*/
class BigBoard
{
    public:

        friend class TicTacToe;
        friend class Cursor;

        explicit BigBoard(Point p0 = Point(0,0), Point p1 = Point(0,0));

        /**
        *   Winner of the board
        */
        std::string getWinner() const {return m_winner;}

        /**
            \brief Method to reset the atributes of the board so it becomes like a new one.
        */
        void reset();

        void setLocations(Point p0, Point p1);

        /**
            \brief Method to draw the whole board.
            \param font Font to use to draw the elements of the board.
        */
        void draw(ALLEGRO_FONT* font) const;

        /**
            \brief Method to mark a board as won by someone.
            \param font Font to use to draw the elements of the board.
        */
        void drawWinner(ALLEGRO_FONT* font) const;

        /**
            \brief Overload of the operator []. This will get you the small board in the received position.
            \param position Position of the small board you want.
            \return Small board in the received position.
        */
        SmallBoard& operator[](Position position) { return m_boards[position]; }
        SmallBoard& operator[](int position) { return m_boards[position]; }

        /**
            \brief Overload of the const operator []. This will get you the small board in the received position.
            \param position Position of the small board you want.
            \return Small board in the received position.
        */
        const SmallBoard& operator[](Position position) const { return m_boards[position]; }
        const SmallBoard& operator[](int position) const { return m_boards[position]; }

        void updateWinner();

    private:
        //Graphic representation related members
        Point m_p0;
        Point m_p1;
        float m_width;
        float m_height;

        //Board's logic related members
        std::string m_winner;
        std::array<SmallBoard, 9> m_boards;
};

#endif // BIGBOARD_H
