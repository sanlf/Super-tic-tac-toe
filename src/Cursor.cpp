#include "../include/Cursor.h"

/**************************************************************************************************/
Cursor::Cursor(const BigBoard& board): m_board(board),
                                       m_p0(m_board.m_p0),
                                       m_p1(m_board.m_p1),
                                       m_mode(Mode::BOARD),
                                       m_boardidx(0),
                                       m_cellidx(0),
                                       m_thickness(3) {}
/**************************************************************************************************/
//repositions the cursor with two new points
void Cursor::reposition(float x, float y)
{
    Point p(x, y);
    //test for all boards until one (or none) contains the point.
    //The idx now becomes the idx of that board and the positions become the positions of
    //that board
    for(int i = 0; i < 9; ++i){
        if(p.isinside(m_board[i].m_p0, m_board[i].m_p1)){
            m_boardidx = i;
            m_p0 = m_board[m_boardidx].m_p0;
            m_p1 = m_board[m_boardidx].m_p1;
            break;
        }
    }
    //test for all cells until one (or none) contains the point.
    //The idx now becomes the idx of that cell and the positions become the positions of
    //that cell
    if(m_mode == Mode::CELL){
        for(auto board : m_board.m_boards){
            for(int i = 0; i < 9; ++i){
                if(p.isinside(board[i].p0, board[i].p1)){
                    m_cellidx = i;
                    m_p0 = board.m_cells[m_boardidx].p0;
                    m_p1 = board.m_cells[m_boardidx].p1;
                    break;
                }
            }
        }
    }
}
void Cursor::reposition(int boardidx)
{
    if(0 <= boardidx && boardidx < 9){
        m_p0 = m_board[boardidx].m_p0;
        m_p1 = m_board[boardidx].m_p1;
        m_boardidx = boardidx;
        m_mode = Mode::BOARD;
    }
}
void Cursor::reposition(int boardidx, int cellidx)
{
    if(0 <= boardidx && boardidx < 9 && 0 <= cellidx && cellidx < 9){
        m_p0 = m_board[boardidx][cellidx].p0;
        m_p1 = m_board[boardidx][cellidx].p1;
        m_boardidx = boardidx;
        m_cellidx = cellidx;
        m_mode = Mode::CELL;
    }
}
/**************************************************************************************************/
//draws the cursor at its position in color
void Cursor::draw(ALLEGRO_COLOR color)
{
    al_draw_rectangle(m_p0.x, m_p0.y, m_p1.x, m_p1.y, color, m_thickness);
}
/**************************************************************************************************/
//moves the cursor in the direction and return the new direction it is in
void Cursor::move(Position position)
{
    if(m_mode == Mode::BOARD){
        if(position == Position::UP){
            if(m_boardidx >= 3) //if board[m_boardidx] is not in the first row
                m_boardidx -= 3;
        }else if(position == Position::DOWN){
            if(m_boardidx < 6) //if board[m_boardidx] is not in the last row
                m_boardidx += 3;
        }else if(position == Position::LEFT){
            if(m_boardidx%3 != 0) //if board[m_boardidx] is not in the first column
                m_boardidx -= 1;
        }else if(position == Position::RIGHT){
            if(m_boardidx%3 != 2) //if board[m_boardidx] is not in the last column
                m_boardidx += 1;
        }
        
        m_p0 = m_board[m_boardidx].m_p0;
        m_p1 = m_board[m_boardidx].m_p1;
    }else{
        if(position == Position::UP){
            if(m_cellidx >= 3) //if board[m_cellidx] is not in the first row
                m_cellidx -= 3;
        }else if(position == Position::DOWN){
            if(m_cellidx < 6) //if board[m_cellidx] is not in the last row
                m_cellidx += 3;
        }else if(position == Position::LEFT){
            if(m_cellidx%3 != 0) //if board[m_cellidx] is not in the first column
                m_cellidx -= 1;
        }else if(position == Position::RIGHT){
            if(m_cellidx%3 != 2) //if board[m_cellidx] is not in the last column
                m_cellidx += 1;
        }

        m_p0 = m_board[m_boardidx][m_cellidx].p0;
        m_p1 = m_board[m_boardidx][m_cellidx].p1;
    }
}
/**************************************************************************************************/

