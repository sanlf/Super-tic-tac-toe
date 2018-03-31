#ifndef POINT_H
#define POINT_H

//Simple coordinate structure. Has x and y.
struct Point{
    float x;
    float y;

    Point() {x = y = 0;}
    Point(float x, float y): x(x), y(y) {}

    //tests if the point is inside a square determinated by the
    //first point being the upper left corner and the second
    //being the lower right corner
    bool isinside(Point upLeftCorner, Point downRightCorner);
};

#endif // POINT_H

