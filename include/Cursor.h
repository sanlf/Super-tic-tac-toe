#ifndef CURSOR_H
#define CURSOR_H

#include <algorithm> //for std::find_if
#include <allegro5/allegro.h> //for ALLEGRO_COLO:
#include <allegro5/allegro_primitives.h> //for draw rectangle
#include <math.h> //for fabs
#include <iostream> //for fabs

#include "Point.h" //for Point struct
#include "Enumerations.h" //for UP, DOWN, LEFT, RIGHT
#include "BigBoard.h" //for BigBoard class
/**
 * Cursor class to move and draw a rectangular cursor in a board
*/

class Cursor{
    public:

    friend class TicTacToe;

    //constructor
    Cursor(const BigBoard& board);

    //repositions the cursor with two new points
    void reposition(float x, float y);
    void reposition(int boardidx);
    void reposition(int boardidx, int cellidx);

    void move(Position position);

    //draws the cursor at its position in color
    void draw(ALLEGRO_COLOR color);
    
    private:
    const BigBoard& m_board;
    Point m_p0;
    Point m_p1;
    Mode m_mode;
    int m_boardidx;
    int m_cellidx;

    int m_thickness;
};

#endif //CURSOR_H

