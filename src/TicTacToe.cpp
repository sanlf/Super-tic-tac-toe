#include "../include/TicTacToe.h"

/**************************************************************************************************/
TicTacToe::TicTacToe(ALLEGRO_DISPLAY* display,
                     ALLEGRO_EVENT_QUEUE* eventQueue,
                     ALLEGRO_TIMER* timer,
                     GameFonts fonts,
                     ALLEGRO_DISPLAY_MODE dispdata):
                                                    m_display(display),
                                                    m_eventQueue(eventQueue),
                                                    m_timer(timer),
                                                    m_fonts(fonts),
                                                    m_dispdata(dispdata),
                                                    m_winner(NO_WINNER),
                                                    m_bboard(Point(0,0), Point(dispdata.width, 0.8*dispdata.height)),
                                                    m_currboardidx(Position::NONE)
{
    m_turn = &m_player1;
    reset("PLAYER1", "X", "PLAYER2", "O");
}
/**************************************************************************************************/
void TicTacToe::play()
{
}
/*
{
    int position = 0;
    if(m_currboardidx == Position::NONE){
        if(m_turn->ishuman()){
            waitForInput();
        }else{ //turn player is ai 
            //play = decideplay();
        }
        //choice board as a human or as ia
        m_currboardidx = chosenboard;
    {

    //chooses and puts a piece in a cell
    putPiece(position);
    updateWinner();
    
    //update winner
    if(winner != NO_WINNER){
        endgame();
    }else{
        if(bboard[position].winner == NO_WINNER)
            m_currboardidx = position;
        else
            m_currboardidx = Position::NONE;

        //puts last play in stack
        plays.push(turn.piece, currboard, position);

        //change turn
        turn = turn == &p1? &p2 : &p1;
    }
}
*/
/**************************************************************************************************/
void TicTacToe::run()
{
    menu();
}
/**************************************************************************************************/
void TicTacToe::menu()
{
    float width = m_dispdata.width;
    float height = m_dispdata.height;
    Point txtpos = Point(width/2.0, 0);

    unsigned short curridx = 0;
    std::array<std::string, 4> menuOption;
    menuOption[0] = "Play";
    menuOption[1] = "Instructions";
    menuOption[2] = "About";
    menuOption[3] = "Exit";

    ALLEGRO_EVENT ev;
    while(ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE){
        al_clear_to_color(COLOR.BACKGROUND);

        //draws title
        txtpos = Point(width/2.0, 0);
        al_draw_text(m_fonts.title, COLOR.WHITE, txtpos.x, txtpos.y, ALLEGRO_ALIGN_CENTER, "TIC-TAC-TOE 81");

        //draws all menu options
        txtpos.y = height/3.0;
        for(auto option : menuOption){
            if(option != menuOption[curridx]){
                al_draw_text(m_fonts.selection,
                             COLOR.WHITE, txtpos.x, txtpos.y,
                             ALLEGRO_ALIGN_CENTER, option.c_str());
            }else{
                al_draw_text(m_fonts.selection,
                             COLOR.GREEN, txtpos.x, txtpos.y,
                             ALLEGRO_ALIGN_CENTER, option.c_str());
            }
            txtpos.y += (3.0/4.0 - 1.0/3.0)*height/menuOption.size();
        }

        al_flip_display();

        al_wait_for_event(m_eventQueue, &ev);

        if(ev.type == ALLEGRO_EVENT_KEY_UP){

            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    if(curridx > 0) --curridx;
                    break;

                case ALLEGRO_KEY_DOWN:
                    if(curridx < menuOption.size() - 1) ++curridx;
                    break;

                case ALLEGRO_KEY_ENTER:
                    if(menuOption[curridx] == "Play"){
                        reset("PLAYER1", "X", "PLAYER2", "O");
                        play();
                    }

                    else if(menuOption[curridx] == "Instructions"){
                        displayInstructions();
                    }

                    else if(menuOption[curridx] == "About"){
                        displayAbout();
                    }

                    else{ //if(menuOption[curridx] == "Exit")
                        ev.type = ALLEGRO_EVENT_DISPLAY_CLOSE;
                    }

                    break;

                case ALLEGRO_KEY_ESCAPE:
                    ev.type = ALLEGRO_EVENT_DISPLAY_CLOSE;
                    break;
            }
        }
    }
}
/**************************************************************************************************/
void TicTacToe::resizeCursorToBoard()
{
    m_currboardidx = Position::NONE;
    cursor.p0 = m_bboard[Position::CENTER].m_p0; //any position will do, just chose center
    cursor.p1 = m_bboard[Position::CENTER].m_p1; //because is the shorter to write
}
/**************************************************************************************************/
void TicTacToe::resizeCursorToCell()
{
    if(m_currboardidx >= 0 && m_currboardidx < 9){
        cursor.p0 = m_bboard[m_currboardidx].m_p0;
        cursor.p1 = m_bboard[m_currboardidx].m_p1;
    }
}
/**************************************************************************************************/
void TicTacToe::displayAbout()
{
    std::string about = readFile("about/about.txt");

    al_clear_to_color(COLOR.BACKGROUND);
    al_draw_multiline_text(m_fonts.files, COLOR.WHITE,
                           10, 10, m_dispdata.width - 10, m_fonts.filesSize, //10 pixel of space
                           ALLEGRO_ALIGN_LEFT, about.c_str());
    al_flip_display();

    handleReturnToMenu(m_eventQueue);
}
/**************************************************************************************************/
void TicTacToe::displayInstructions()
{
    std::string instructions = readFile("man/instructions.txt");

    al_clear_to_color(COLOR.BACKGROUND);
    al_draw_multiline_text(m_fonts.files, COLOR.WHITE,
                           10, 10, m_dispdata.width - 10, m_fonts.filesSize, //10 pixel of space
                           ALLEGRO_ALIGN_LEFT, instructions.c_str());
    al_flip_display();

    handleReturnToMenu(m_eventQueue);
}
/**************************************************************************************************/
void TicTacToe::reset(std::string nameP1, std::string pieceP1, std::string nameP2, std::string pieceP2)
{
    m_winner = NO_WINNER;
    m_player1.setName(nameP1);
    m_player1.setPiece(pieceP1);
    m_player2.setName(nameP2);
    m_player2.setPiece(pieceP2);

    m_currboardidx = Position::NONE;
    m_turn = &m_player1;

    m_bboard.reset();
    
    //empy the stack of plays

    resizeCursorToBoard();
}
/**************************************************************************************************/

