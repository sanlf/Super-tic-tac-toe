#ifndef CURSOR_H
#define CURSOR_H

#include <allegro5/allegro.h> //for ALLEGRO_COLO:
#include <allegro5/allegro_primitives.h> //for draw rectangle
#include <math.h> //for fabs

#include "Point.h" //for Point struct
#include "Enumerations.h" //for UP, DOWN, LEFT, RIGHT
/**
 * Cursor class to move and draw a rectangular cursor in a board
*/

struct Cursor{
    Point p0;
    Point p1;

    int thickness;

    //constructor
    Cursor(Point p0 = Point(0,0), Point p1 = Point(0,0)): p0(p0), p1(p1) {}

    //repositions the cursor with two new points
    void reposition(Point p0, Point p1);

    void move(Position position);

    //draws the cursor at its position in color
    void draw(ALLEGRO_COLOR color);
};

#endif //CURSOR_H

