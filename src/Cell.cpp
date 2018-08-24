#include "../include/Cell.h"

/**************************************************************************************************/
Cell::Cell()
{
    p0 = Point(0, 0);
    p1 = Point(0, 0);
    piece = "";
}
/**************************************************************************************************/
Cell::Cell(Point p0, Point p1, std::string piece/* = ""*/)
{
    this->p0 = p0;
    this->p1 = p1;
    this->piece = piece;
}
/**************************************************************************************************/
void Cell::draw(ALLEGRO_FONT* font) const
{
    ALLEGRO_COLOR color = this->piece == "X"? COLOR.CURSOR_P1 : COLOR.CURSOR_P2;
    al_draw_text(font, color,
                 (2*p0.x + p1.x)/3.0, (2*p0.y + p1.y)/3.0,
                 ALLEGRO_ALIGN_LEFT, piece.c_str());
}
/**************************************************************************************************/

