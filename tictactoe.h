#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream> //for cout and endl

#include <memory> //for shared_ptr
#include <allegro5/allegro.h> //for most of the game
#include <allegro5/allegro_native_dialog.h> //for native box messages
#include <allegro5/allegro_primitives.h> //for drawing rectangles and lines

#include "Player.h" //fot Player
#include "Board/BigBoard.h" //for BigBoard
#include "../AllegroColors.h" //for Colors
#include "Redefinitions.h" //for various redefinitions
#include "../Window.h"
#include "TicTacToeConstants.h" //for NO_WINNER, TIE
#include "Utilities.h" //for auxiliar functions and structs

#define WAIT_TIME 0.35 //wait time of timer

/**
    \brief Class TicTacToe. With this you can play a game of TicTacToe81.
    \pre You must have loaded allegro before attempting to run this game.
    \author Sotomayor Samaniego Luis Fernando.
    \date 2017/06/02
    \version 1.0
*/

class TicTacToe
{
public:

    /**
        \brief Constructor of a TicTacToe game. Initializes all the relevant
                parameter for the game.
        \pre This game uses allegro for display so it must be already loaded. The general library,
                font and ttf addons, keyboard, display, event queue, timer and various fonts the game
                needs.
        \param display Display where the game is going to be .
        \param eventQueue Event queue needed to handle events of the game.
        \param timer Timer for blinking of selected square in the game.
        \param normalFont Font most of the game element uses.
        \param titleFont Font for the title of the game in the menu.
        \param selectionFont Font for the posible options in the menu.
        \param filesFont Font to output the instruction and about texts.
        \param window Structure with the sizes of the window and screen.
    */
    TicTacToe();
    
    //Destructor
    ~TicTacToe();

    /**
        \brief Method to play the game. This is run in order to actually play.
    */
    void play();

    /**
        \brief Method to start the game. When starting, you are loaded to the menu.
    */
    void run();

    /**
        \brief Method to output the menu of the game. You can select to play, exit, and look at instructions.
    */
    void menu();

    /**
        \brief Method to display the about option from the menu.
    */
    void displayAbout();

    /**
        \brief Method to display the instructions from the menu.
    */
    void displayInstructions();

    /**
        \brief Method to put a piece in a cell of a small board.
    */
    void putPiece(std::string piece, SmallBoard& board, unsigned cell);

    /**
        \brief Method to end the current game showing the winner if there is any.
    */
    void endgame();

private:
    int winner;
    BigBoard bboard;
    int turn;
    SmallBoard currboard;
    Stack plays; 

    Player p1;
    Player p2;
};

