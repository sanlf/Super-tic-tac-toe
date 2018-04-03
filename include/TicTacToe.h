#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string> //for std::string
#include <iostream>

#include <allegro5/allegro.h> //for most of the game
#include <allegro5/allegro_native_dialog.h> //for native box messages
#include <allegro5/allegro_primitives.h> //for drawing rectangles and lines

#include "Player.h" //for Player
#include "BigBoard.h" //for BigBoard
#include "Colors.h" //for Colors
#include "Constants.h" //for NO_WINNER, TIE
#include "Enumerations.h" //for Type and Position enumerations
#include "Utilities.h" //for auxiliar functions and structs
#include "GameFonts.h" //for various fonts the game uses
#include "Cursor.h" //for a cursor of the game

extern Colors COLOR;

/**
    \brief Class TicTacToe. With this you can play a game of TicTacToe81.
    \pre You must have loaded allegro before attempting to run this game.
    \author Sotomayor Samaniego Luis Fernando.
    \date 2017/06/02
    \version 1.0
*/

class TicTacToe{
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
    TicTacToe(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* eventQueue, ALLEGRO_TIMER* timer, GameFonts fonts, ALLEGRO_DISPLAY_MODE dispdata);
    
    void reset(std::string nameP1, std::string pieceP1, std::string nameP2, std::string pieceP2, Type typePlayer2 = Type::HUMAN);

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
    bool putPiece(int cellidx);

    void draw() const;

    /**
        \brief Method to end the current game showing the winner if there is any.
    */
    void endgame();

    void handleUserInput(ALLEGRO_EVENT* ev);
    void handleKeyboardInput(ALLEGRO_EVENT* ev);

    void updateWinner();

    bool selectBoard(int position);
    bool selectCell(int position);

    void changeTurn() {m_turn = m_turn == &m_player1 ? &m_player2 : &m_player1;}

    void drawGameInfo() const;

    void drawBoardWinners() const;

    //changes the color of the cursor indicating there was an error and stops momentarily
    //the program in order to see it
    void drawCursorError() const;

private:
    //Graphic representation related members
    ALLEGRO_DISPLAY* m_display;
    ALLEGRO_EVENT_QUEUE* m_eventQueue;
    ALLEGRO_TIMER* m_timer;    
    GameFonts m_fonts;
    ALLEGRO_DISPLAY_MODE m_dispdata;
    Cursor m_cursor;

    //Game's logic related members
    std::string m_winner;
    BigBoard m_bboard;
    Position m_currboardidx;
    Player m_player1;
    Player m_player2;
    Player* m_turn;
    //Stack m_plays; //Stack of plays
};

#endif //TICTACTOE_H

