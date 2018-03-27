#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate{
    float x;
    float y;

    Coordinate() {x = y = 0}
    Coordinate(float x, y): x(x), y(y) {}
};

#endif // COORDINATE_H

