#include "../include/SmallBoard.h"

/**************************************************************************************************/
SmallBoard::SmallBoard(Point p0, Point p1)
{
    float spacex = 0.05 * fabs(p0.x - p1.x);
    float spacey = 0.05 * fabs(p0.y - p1.y);

    m_p0 = Point(p0.x + spacex, p0.y + spacey);
    m_p1 = Point(p1.x - spacex, p1.y - spacey);

    m_width = fabs(m_p0.x - m_p1.x);
    m_height = fabs(m_p0.y - m_p1.y);

    this->resetlocation(p0, p1);
}
/**************************************************************************************************/
void SmallBoard::resetlocation(Point p0, Point p1)
{
    m_p0 = p0;
    m_p1 = p1;

    float cwidth = m_width / 3.0;
    float cheight = m_height / 3.0;
    
    for(int i = 0; i < 9; ++i){
        m_cells[i].p0 = Point(m_p0.x + (i % 3) * cwidth,
                              m_p0.y + (i / 3) * cheight);
        m_cells[i].p1 = Point(m_p1.x + (i%3 + 1) * cwidth,
                              m_p1.y + (i/3 + 1) * cheight);
    }
}
/**************************************************************************************************/
void SmallBoard::reset()
{
    for(auto cell : m_cells)
        cell.reset(); 

    //for(auto it = m_winningLine.begin(); m_winningLine.end(); ++it)
    //  *it = -1;

    m_winner = NO_WINNER;
}
/**************************************************************************************************/
void SmallBoard::draw(ALLEGRO_FONT* font) const
{
    //vertical lines
    al_draw_line(m_cells[0].p1.x, m_cells[0].p0.y, m_cells[0].p1.x, m_cells[8].p1.y, COLOR.BOARD_COLOR, 3);
    al_draw_line(m_cells[1].p1.x, m_cells[0].p0.y, m_cells[1].p1.x, m_cells[8].p1.y, COLOR.BOARD_COLOR, 3);
    //horizontal lines
    al_draw_line(m_cells[0].p0.x, m_cells[0].p1.y, m_cells[8].p1.x, m_cells[0].p1.y, COLOR.BOARD_COLOR, 3);
    al_draw_line(m_cells[0].p0.x, m_cells[3].p1.y, m_cells[8].p1.x, m_cells[3].p1.y, COLOR.BOARD_COLOR, 3);


    //writes the letter in the cells
    for(auto cell : m_cells)
        cell.draw(font); 

    this->drawWinner(font); 
}
/**************************************************************************************************/
void SmallBoard::drawWinner(ALLEGRO_FONT* font) const
{
    if(m_winner == NO_WINNER){
        return;
    }

    Point p0;
    Point p1;

    //left to right diagonal
    if(m_cells[Position::CENTER].piece == m_winner &&
       m_cells[Position::CENTER].piece == m_cells[Position::LEFT_UP].piece &&
       m_cells[Position::CENTER].piece == m_cells[Position::RIGHT_DOWN].piece){
        p0.x = m_p0.x;
        p0.y = m_p0.y;
        p1.x = m_p1.x;
        p1.y = m_p1.y;
    }
    //right to left diagonal
    if(m_cells[Position::CENTER].piece == m_winner &&
       m_cells[Position::CENTER].piece == m_cells[Position::RIGHT_UP].piece &&
       m_cells[Position::CENTER].piece == m_cells[Position::LEFT_DOWN].piece){
        p0.x = m_p0.x;
        p0.y = m_p1.y;
        p1.x = m_p1.x;
        p1.y = m_p0.y;
    }
    //horizontal center
    if(m_cells[Position::CENTER].piece == m_winner &&
       m_cells[Position::CENTER].piece == m_cells[Position::LEFT_CENTER].piece &&
       m_cells[Position::CENTER].piece == m_cells[Position::RIGHT_CENTER].piece){
        p0.x = m_p0.x;
        p0.y = m_p0.y + m_height/2.0;
        p1.x = m_p1.x;
        p1.y = p0.y;
    }
    //vertical center
    if(m_cells[Position::CENTER].piece == m_winner &&
       m_cells[Position::CENTER].piece == m_cells[Position::CENTER_UP].piece &&
       m_cells[Position::CENTER].piece == m_cells[Position::CENTER_DOWN].piece){
        p0.x = m_p0.x + m_width/2.0;
        p0.y = m_p0.y;
        p1.x = p0.x;
        p1.y = m_p0.y;
    }

    //horizontal up
    if(m_cells[Position::LEFT_UP].piece == m_winner &&
       m_cells[Position::LEFT_UP].piece == m_cells[Position::CENTER_UP].piece &&
       m_cells[Position::LEFT_UP].piece == m_cells[Position::RIGHT_UP].piece){
        p0.x = m_p0.x;
        p0.y = m_p0.y + m_height/6.0;
        p1.x = m_p1.x;
        p1.y = p0.y;
    }
    //vertical left
    if(m_cells[Position::LEFT_UP].piece == m_winner &&
       m_cells[Position::LEFT_UP].piece == m_cells[Position::LEFT_CENTER].piece &&
       m_cells[Position::LEFT_UP].piece == m_cells[Position::LEFT_DOWN].piece){
        p0.x = m_p0.x + m_width/6.0;
        p0.y = m_p0.y;
        p1.x = p0.x;
        p1.y = m_p1.y;
    }

    //horizontal down
    if(m_cells[Position::RIGHT_DOWN].piece == m_winner &&
       m_cells[Position::RIGHT_DOWN].piece == m_cells[Position::LEFT_DOWN].piece &&
       m_cells[Position::RIGHT_DOWN].piece == m_cells[Position::CENTER_DOWN].piece){
        p0.x = m_p0.x;
        p0.y = m_p1.y - m_height/6.0;
        p1.x = m_p1.x;
        p1.y = p0.y;
    }
    //vertical right
    if(m_cells[Position::RIGHT_DOWN].piece == m_winner &&
       m_cells[Position::RIGHT_DOWN].piece == m_cells[Position::RIGHT_UP].piece &&
       m_cells[Position::RIGHT_DOWN].piece == m_cells[Position::RIGHT_CENTER].piece){
        p0.x = m_p1.x - m_width/6.0;
        p0.y = m_p0.y;
        p1.x = p0.x;
        p1.y = m_p1.y;
    }

    al_draw_line(p0.x, p0.y, p1.x, p1.y, COLOR.WHITE, LINE_THICKNESS);
}
/**************************************************************************************************/
std::string SmallBoard::checkWinner()
{
    if(m_winner != NO_WINNER)
       return m_winner; 

    //left to right diagonal
    if(m_cells[Position::CENTER].piece == EMPTY &&
       m_cells[Position::CENTER].piece == m_cells[Position::LEFT_UP].piece &&
       m_cells[Position::CENTER].piece == m_cells[Position::RIGHT_DOWN].piece)
        m_winner = m_cells[Position::CENTER].piece;
    
    //right to left diagonal
    if(m_cells[Position::CENTER].piece == EMPTY &&
       m_cells[Position::CENTER].piece == m_cells[Position::RIGHT_UP].piece &&
       m_cells[Position::CENTER].piece == m_cells[Position::LEFT_DOWN].piece)
        m_winner = m_cells[Position::CENTER].piece;
    
    //horizontal center
    if(m_cells[Position::CENTER].piece == EMPTY &&
       m_cells[Position::CENTER].piece == m_cells[Position::LEFT_CENTER].piece &&
       m_cells[Position::CENTER].piece == m_cells[Position::RIGHT_CENTER].piece)
        m_winner = m_cells[Position::CENTER].piece;
    
    //vertical center
    if(m_cells[Position::CENTER].piece == EMPTY &&
       m_cells[Position::CENTER].piece == m_cells[Position::CENTER_UP].piece &&
       m_cells[Position::CENTER].piece == m_cells[Position::CENTER_DOWN].piece)
        m_winner = m_cells[Position::CENTER].piece;
    
    //horizontal up
    if(m_cells[Position::LEFT_UP].piece == EMPTY &&
       m_cells[Position::LEFT_UP].piece == m_cells[Position::CENTER_UP].piece &&
       m_cells[Position::LEFT_UP].piece == m_cells[Position::RIGHT_UP].piece)
        m_winner = m_cells[Position::LEFT_UP].piece;
    
    //vertical left
    if(m_cells[Position::LEFT_UP].piece == EMPTY &&
       m_cells[Position::LEFT_UP].piece == m_cells[Position::LEFT_CENTER].piece &&
       m_cells[Position::LEFT_UP].piece == m_cells[Position::LEFT_DOWN].piece)
        m_winner = m_cells[Position::LEFT_UP].piece;

    //horizontal down
    if(m_cells[Position::RIGHT_DOWN].piece == EMPTY &&
       m_cells[Position::RIGHT_DOWN].piece == m_cells[Position::LEFT_DOWN].piece &&
       m_cells[Position::RIGHT_DOWN].piece == m_cells[Position::CENTER_DOWN].piece)
        m_winner = m_cells[Position::RIGHT_DOWN].piece;
    
    //vertical right
    if(m_cells[Position::RIGHT_DOWN].piece == EMPTY &&
       m_cells[Position::RIGHT_DOWN].piece == m_cells[Position::RIGHT_UP].piece &&
       m_cells[Position::RIGHT_DOWN].piece == m_cells[Position::RIGHT_CENTER].piece)
        m_winner = m_cells[Position::RIGHT_DOWN].piece;

    if(std::all_of(m_cells.begin(), m_cells.end(), [](auto cell){return cell.piece != EMPTY;}))
        m_winner = TIE;
     
    return m_winner;
}
/**************************************************************************************************/

