#ifndef SMALLBOARD_H
#define SMALLBOARD_H

#include <array> //for std::array
#include <algorithm> //for std::all_of
#include <string> //for string
#include <math.h> //for fabs

#include <allegro5/allegro.h> //for draw primitives
#include <allegro5/allegro_primitives.h> //for draw primitives
#include <allegro5/allegro_font.h> //for allegro font

#include "Point.h" //for Point struct
#include "Colors.h" //for Colors global variable
#include "Enumerations.h" //for Position enumeration
#include "Constants.h" //for NO_WINNER
#include "Cell.h" //for Cell struct

extern Colors COLOR;

/**
    \brief Class SmallBoard which has an array of cells.
    \author Sotomayor Samaniego Luis Fernando.
    \date 2017/06/02
    \version 1.0
*/

class SmallBoard
{
    public:

        friend class TicTacToe;
        friend class BigBoard;
        friend class Cursor;
        
        explicit SmallBoard(Point p0 = Point(0,0), Point p1 = Point(0,0));

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
            \param display Display where the board will be drawn.
            \param font Font to use to draw the elements of the board.
        */
        void draw(ALLEGRO_FONT* font) const;

        /**
            \brief Method to mark a board as won by someone.
            \param display Display where the board will be drawn.
            \param font Font to use to draw the elements of the board.
        */
        void drawWinner() const;

        /**
            \brief Overload of the operator []. This will get you the small board in the received position.
            \param position Position of the small board you want.
            \return Small board in the received position.
        */
        //std::string& operator[](Position position) { return m_cells[position].piece; }
        //std::string& operator[](int position) { return m_cells[position].piece; }
        Cell& operator[](Position position) { return m_cells[position]; }
        Cell& operator[](int position) { return m_cells[position]; }

        /**
            \brief Overload of the const operator []. This will get you the small board in the received position.
            \param position Position of the small board you want.
            \return Small board in the received position.
        */
        //const std::string& operator[](Position position) const { return m_cells[position].piece; }
        //const std::string& operator[](int position) const { return m_cells[position].piece; }
        const Cell& operator[](Position position) const { return m_cells[position]; }
        const Cell& operator[](int position) const { return m_cells[position]; }

        void updateWinner();

    private:
        //Graphic representation related members
        Point m_p0;
        Point m_p1;
        float m_width;
        float m_height;

        //Board's logic related members
        std::string m_winner;
        std::array<Cell, 9> m_cells;
};

#endif // SMALLBOARD_H
