#include "../include/Point.h"

/**************************************************************************************************/
bool Point::isinside(Point upLeftCorner, Point downRightCorner)
{
    return upLeftCorner.x <= x && x <= downRightCorner.x &&
           upLeftCorner.y <= y && y <= downRightCorner.y;
}
/**************************************************************************************************/
