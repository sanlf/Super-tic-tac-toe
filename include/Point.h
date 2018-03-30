#ifndef POINT_H
#define POINT_H

//Simple coordinate structure. Has x and y.
struct Point{
    float x;
    float y;

    Point() {x = y = 0;}
    Point(float x, float y): x(x), y(y) {}
};

#endif // POINT_H

