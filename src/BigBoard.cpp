#include "../include/BigBoard.h"

/**************************************************************************************************/
BigBoard::BigBoard(Point p0, Point p1)
{
    this->setLocations(p0, p1);

    m_winner = NO_WINNER;
}
/**************************************************************************************************/
void BigBoard::setLocations(Point p0, Point p1)
{
    float spacex    = 0.05 * fabs(p0.x - p1.x);
    float spacey    = 0.05 * fabs(p0.y - p1.y);

    m_p0            = Point(p0.x + spacex, p0.y + spacey);
    m_p1            = Point(p1.x - spacex, p1.y - spacey);

    m_width         = fabs(m_p0.x - m_p1.x);
    m_height        = fabs(m_p0.y - m_p1.y);


    float sbwidth   = m_width / 3.0;
    float sbheight  = m_height / 3.0;
    
    for(int i = 0; i < 9; ++i){
        Point pa(m_p0.x + (i%3) * sbwidth, m_p0.y + (i/3) * sbheight);
        Point pb(pa.x + sbwidth, pa.y + sbheight);
        m_boards[i].setLocations(pa, pb);
    }
}
/**************************************************************************************************/
void BigBoard::reset()
{
    for(auto& board : m_boards)
        board.reset();

    m_winner = NO_WINNER;
}
/**************************************************************************************************/
void BigBoard::draw(ALLEGRO_FONT* font) const
{
    //vertical lines
    //al_draw_line(m_boards[0].m_p1.x, m_boards[0].m_p0.y, m_boards[0].m_p1.x, m_boards[8].m_p1.y, COLOR.BOARD_COLOR, 3);
    //al_draw_line(m_boards[1].m_p1.x, m_boards[0].m_p0.y, m_boards[1].m_p1.x, m_boards[8].m_p1.y, COLOR.BOARD_COLOR, 3);
    al_draw_line(m_p0.x + 1.0*m_width/3.0, m_p0.y, m_p0.x + 1.0*m_width/3.0, m_p1.y, COLOR.BOARD_COLOR, 3);
    al_draw_line(m_p0.x + 2.0*m_width/3.0, m_p0.y, m_p0.x + 2.0*m_width/3.0, m_p1.y, COLOR.BOARD_COLOR, 3);
    //horizontal lines
    //al_draw_line(m_boards[0].m_p0.x, m_boards[0].m_p1.y, m_boards[8].m_p1.x, m_boards[0].m_p1.y, COLOR.BOARD_COLOR, 3);
    //al_draw_line(m_boards[0].m_p0.x, m_boards[3].m_p1.y, m_boards[8].m_p1.x, m_boards[3].m_p1.y, COLOR.BOARD_COLOR, 3);
    al_draw_line(m_p0.x, m_p0.y + 1.0*m_height/3.0, m_p1.x, m_p0.y + 1.0*m_height/3.0, COLOR.BOARD_COLOR, 3);
    al_draw_line(m_p0.x, m_p0.y + 2.0*m_height/3.0, m_p1.x, m_p0.y + 2.0*m_height/3.0, COLOR.BOARD_COLOR, 3);

    for(const auto& board : m_boards)
        board.draw(font); 
}
/**************************************************************************************************/
void BigBoard::drawWinner() const
{
    if(m_winner == NO_WINNER)
        return;

    Point p0;
    Point p1;

    //left to right diagonal
    if(m_boards[Position::CENTER].m_winner == m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::LEFT_UP].m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::RIGHT_DOWN].m_winner){
        p0.x = m_p0.x;
        p0.y = m_p0.y;
        p1.x = m_p1.x;
        p1.y = m_p1.y;
    }
    //right to left diagonal
    if(m_boards[Position::CENTER].m_winner == m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::RIGHT_UP].m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::LEFT_DOWN].m_winner){
        p0.x = m_p0.x;
        p0.y = m_p1.y;
        p1.x = m_p1.x;
        p1.y = m_p0.y;
    }
    //horizontal center
    if(m_boards[Position::CENTER].m_winner == m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::LEFT_CENTER].m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::RIGHT_CENTER].m_winner){
        p0.x = m_p0.x;
        p0.y = m_p0.y + m_height/2.0;
        p1.x = m_p1.x;
        p1.y = p0.y;
    }
    //vertical center
    if(m_boards[Position::CENTER].m_winner == m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::CENTER_UP].m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::CENTER_DOWN].m_winner){
        p0.x = m_p0.x + m_width/2.0;
        p0.y = m_p0.y;
        p1.x = p0.x;
        p1.y = m_p1.y;
    }

    //horizontal up
    if(m_boards[Position::LEFT_UP].m_winner == m_winner &&
       m_boards[Position::LEFT_UP].m_winner == m_boards[Position::CENTER_UP].m_winner &&
       m_boards[Position::LEFT_UP].m_winner == m_boards[Position::RIGHT_UP].m_winner){
        p0.x = m_p0.x;
        p0.y = m_p0.y + m_height/6.0;
        p1.x = m_p1.x;
        p1.y = p0.y;
    }
    //vertical left
    if(m_boards[Position::LEFT_UP].m_winner == m_winner &&
       m_boards[Position::LEFT_UP].m_winner == m_boards[Position::LEFT_CENTER].m_winner &&
       m_boards[Position::LEFT_UP].m_winner == m_boards[Position::LEFT_DOWN].m_winner){
        p0.x = m_p0.x + m_width/6.0;
        p0.y = m_p0.y;
        p1.x = p0.x;
        p1.y = m_p1.y;
    }

    //horizontal down
    if(m_boards[Position::RIGHT_DOWN].m_winner == m_winner &&
       m_boards[Position::RIGHT_DOWN].m_winner == m_boards[Position::LEFT_DOWN].m_winner &&
       m_boards[Position::RIGHT_DOWN].m_winner == m_boards[Position::CENTER_DOWN].m_winner){
        p0.x = m_p0.x;
        p0.y = m_p1.y - m_height/6.0;
        p1.x = m_p1.x;
        p1.y = p0.y;
    }
    //vertical right
    if(m_boards[Position::RIGHT_DOWN].m_winner == m_winner &&
       m_boards[Position::RIGHT_DOWN].m_winner == m_boards[Position::RIGHT_UP].m_winner &&
       m_boards[Position::RIGHT_DOWN].m_winner == m_boards[Position::RIGHT_CENTER].m_winner){
        p0.x = m_p1.x - m_width/6.0;
        p0.y = m_p0.y;
        p1.x = p0.x;
        p1.y = m_p1.y;
    }

    al_draw_line(p0.x, p0.y, p1.x, p1.y, COLOR.WHITE, LINE_THICKNESS);
}
/**************************************************************************************************/
void BigBoard::updateWinner()
{
    if(m_winner != NO_WINNER) //if there is already a winner there is no reason to check
        return;

    for(auto& board : m_boards)
        board.updateWinner();

    //left to right diagonal
    if(m_boards[Position::CENTER].m_winner != EMPTY &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::LEFT_UP].m_winner &&
       m_boards[Position::CENTER].m_winner == m_boards[Position::RIGHT_DOWN].m_winner)
        m_winner = m_boards[Position::CENTER].m_winner;
    
    //right to left diagonal
    else if(m_boards[Position::CENTER].m_winner != EMPTY &&
            m_boards[Position::CENTER].m_winner == m_boards[Position::RIGHT_UP].m_winner &&
            m_boards[Position::CENTER].m_winner == m_boards[Position::LEFT_DOWN].m_winner)
        m_winner = m_boards[Position::CENTER].m_winner;
    
    //horizontal center
    else if(m_boards[Position::CENTER].m_winner != EMPTY &&
            m_boards[Position::CENTER].m_winner == m_boards[Position::LEFT_CENTER].m_winner &&
            m_boards[Position::CENTER].m_winner == m_boards[Position::RIGHT_CENTER].m_winner)
        m_winner = m_boards[Position::CENTER].m_winner;
    
    //vertical center
    else if(m_boards[Position::CENTER].m_winner != EMPTY &&
            m_boards[Position::CENTER].m_winner == m_boards[Position::CENTER_UP].m_winner &&
            m_boards[Position::CENTER].m_winner == m_boards[Position::CENTER_DOWN].m_winner)
        m_winner = m_boards[Position::CENTER].m_winner;
    
    //horizontal up
    else if(m_boards[Position::LEFT_UP].m_winner != EMPTY &&
            m_boards[Position::LEFT_UP].m_winner == m_boards[Position::CENTER_UP].m_winner &&
            m_boards[Position::LEFT_UP].m_winner == m_boards[Position::RIGHT_UP].m_winner)
        m_winner = m_boards[Position::LEFT_UP].m_winner;
    
    //vertical left
    else if(m_boards[Position::LEFT_UP].m_winner != EMPTY &&
            m_boards[Position::LEFT_UP].m_winner == m_boards[Position::LEFT_CENTER].m_winner &&
            m_boards[Position::LEFT_UP].m_winner == m_boards[Position::LEFT_DOWN].m_winner)
        m_winner = m_boards[Position::LEFT_UP].m_winner;

    //horizontal down
    else if(m_boards[Position::RIGHT_DOWN].m_winner != EMPTY &&
            m_boards[Position::RIGHT_DOWN].m_winner == m_boards[Position::LEFT_DOWN].m_winner &&
            m_boards[Position::RIGHT_DOWN].m_winner == m_boards[Position::CENTER_DOWN].m_winner)
        m_winner = m_boards[Position::RIGHT_DOWN].m_winner;
    
    //vertical right
    else if(m_boards[Position::RIGHT_DOWN].m_winner != EMPTY &&
            m_boards[Position::RIGHT_DOWN].m_winner == m_boards[Position::RIGHT_UP].m_winner &&
            m_boards[Position::RIGHT_DOWN].m_winner == m_boards[Position::RIGHT_CENTER].m_winner)
        m_winner = m_boards[Position::RIGHT_DOWN].m_winner;

    //finally checks if there is a tie
    else if(std::all_of(m_boards.begin(), m_boards.end(),
            [](const auto& board){return board.getWinner() == TIE;}))
        m_winner = TIE;
}
/**************************************************************************************************/

