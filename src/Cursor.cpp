#include "../include/Cursor.h"

/**************************************************************************************************/
//repositions the cursor with two new points
void Cursor::reposition(Point p0, Point p1)
{
    p0 = p0;
    p1 = p1;
    thickness = 3;
}
/**************************************************************************************************/
//draws the cursor at its position in color
void Cursor::draw(ALLEGRO_COLOR color)
{
    al_draw_rectangle(p0.x, p0.y, p1.x, p1.y, color, thickness);
}
/**************************************************************************************************/
//moves the cursor in the direction
void Cursor::move(Position position)
{
    float width = fabs(p0.x - p1.x);
    float height = fabs(p0.y - p1.y);

    if(position == Position::UP){
        p0.y -= height;
        p1.y -= height;
    }else if(position == Position::DOWN){
        p0.y += height;
        p1.y += height;
    }else if(position == Position::LEFT){
        p0.x -= width;
        p1.x -= width;
    }else{ //if(position == Position::RIGHT){
        p0.x += width;
        p1.x += width;
    }
}
/**************************************************************************************************/

