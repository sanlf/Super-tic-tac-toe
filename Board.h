#ifndef BOARD_H
#define BOARD_H

#include <vector>


/**
    \brief Board interface of tic-tac-toe. This interface has the minimum functionality a board needs.
    \author Sotomayor Samaniego Luis Fernando.
    \date 2017/05/28
    \version 1.0
*/

class Board
{
    public:

        /**
        *   Access to the array
        */
        auto& operator[](unsigned position) = 0;
        const auto& operator[](unsigned position) const = 0;

        /**
        *   Winner of the board
        */
        int getWinner() const {return winner}

        /**
        *   Winning move (if there is no winner then return error
        */
        auto getWinningLine() const {return winningLine}

        /**
        *   Draws the board
        */
        void draw() = 0;

        /**
        *  Resets the attributes of the class
        */
        void reset() = 0;

    private:
        int winner;
        std::vector<unsigned> winningLine;
        GraphicInfo goodname;
};

#endif // BOARD_H
