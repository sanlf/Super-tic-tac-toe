
SmallBoard(Coordinate p0, Coordinate p1)
{
    float spacex = 0.05 * fabs(p0.x - p1.x);
    float spacey = 0.05 * fabs(p0.y - p1.y);
    //initiates the coordinates
    this->p0 = Coordinate(p0.x + spacex, p0.y + spacey);
    this->p1 = Coordinate(p1.x - spacex, p1.y - spacey);

    this->width = fabs(this->p0.x - this->p1.x);
    this->height = fabs(this->p0.y - this->p1.y);

    for(int i = 0; i < 9; ++i){
        cells[i].p0 = Coordinate(this->p0.x + (i % 3) * cwidth,
                                 this->p0.y + (i / 3) * cheight);
        cells[i].p1 = Coordinate(this->p1.x + (i%3 + 1) * cwidth,
                                 this->p1.y + (i/3 + 1) * cheight);
    }
}
