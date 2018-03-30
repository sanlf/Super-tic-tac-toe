#ifndef CELL_H
#define CELL_H

#include <string> //for std::string
#include <allegro5/allegro_font.h> //for allegro font
#include "Point.h" //for struct Point
#include "Colors.h" //for colors global variable

extern Colors COLOR;

struct Cell{
    std::string piece;
    Point p0;
    Point p1;

    Cell();
    Cell(Point p0, Point p1, std::string piece = "");

    void reset() {piece = "";}

    void draw(ALLEGRO_FONT* font) const;
};

#endif // CELL_H

