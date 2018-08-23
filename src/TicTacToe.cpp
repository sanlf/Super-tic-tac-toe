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
                                                    m_cursor(m_bboard),
                                                    m_winner(NO_WINNER),
                                                    m_bboard(Point(0,0),
                                                             Point(dispdata.width,
                                                                   0.8*dispdata.height)),
                                                    m_currboardidx(Position::NONE),
                                                    m_player1("J1", "X",
                                                              Type::HUMAN,
                                                              m_bboard,
                                                              COLOR.CURSOR_P1),
                                                    m_player2("J2", "O",
                                                              Type::HUMAN,
                                                              m_bboard,
                                                              COLOR.CURSOR_P2)
{
    m_turn = &m_player1;
    reset("JUGADOR1", "X", "JUGADOR2", "O");
}
/**************************************************************************************************/
void TicTacToe::play()
{
    bool redraw = true;
    ALLEGRO_EVENT ev;

    //this lambda tells wheter escape was pressed or not
    auto closegame = [](ALLEGRO_EVENT e){return e.type == ALLEGRO_EVENT_KEY_UP &&
                                         e.keyboard.keycode == ALLEGRO_KEY_ESCAPE;};

    al_start_timer(m_timer);
    while(m_winner == NO_WINNER && !closegame(ev)){
        al_wait_for_event(m_eventQueue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        if(redraw && al_is_event_queue_empty(m_eventQueue)){
            redraw = false;

            draw();
        }

        if(m_turn->getType() == Type::HUMAN){
            handleUserInput(&ev);
        }else{
            std::pair<Position, Position> aiPlay;

            aiPlay = m_turn->agentDecision(m_currboardidx);

            if(m_currboardidx == Position::NONE){
                selectBoard(aiPlay.first);
            }

            selectCell(aiPlay.second);
        }
    }

    endgame();

    al_flush_event_queue(m_eventQueue); //clean the event queue after playing
}
/**************************************************************************************************/
void TicTacToe::endgame()
{
    if(m_winner != NO_WINNER){

        draw();

        if(m_winner != TIE){
             std::string msg = ", ganaste!";
             Player* winner = m_player1.getPiece() == m_winner ? &m_player1 : &m_player2;
             al_show_native_message_box(m_display,
                                        "Felicidades!",
                                        "Felicidades!",
                                        (winner->getName() + msg).c_str(),
                                        nullptr, ALLEGRO_MESSAGEBOX_OK_CANCEL );
         }else{
             std::string msg = "El juego terminó en empate";
             al_show_native_message_box(m_display,
                                        "Empate",
                                        "Empate",
                                        msg.c_str(),
                                        nullptr, ALLEGRO_MESSAGEBOX_OK_CANCEL );
         }
    }
}
/**************************************************************************************************/
void TicTacToe::handleUserInput(ALLEGRO_EVENT* ev)
{
    if(ev->type == ALLEGRO_EVENT_KEY_UP){ //handles keyboard
        handleKeyboardInput(ev);
    }//else if(ev->type == ALLEGRO_MOUSE_SOMETHING??)
}
/**************************************************************************************************/
void TicTacToe::handleKeyboardInput(ALLEGRO_EVENT* ev)
{
   switch(ev->keyboard.keycode){
        case ALLEGRO_KEY_UP:
                m_cursor.move(Position::UP);
            break;

        case ALLEGRO_KEY_DOWN:
                m_cursor.move(Position::DOWN);
            break;

        case ALLEGRO_KEY_LEFT:
                m_cursor.move(Position::LEFT);
            break;

        case ALLEGRO_KEY_RIGHT:
                m_cursor.move(Position::RIGHT);
            break;

        case ALLEGRO_KEY_ENTER:
            if(m_currboardidx == Position::NONE){
                if(!selectBoard(m_cursor.m_boardidx))   //if an invalid board was selected
                    drawCursorError();
            }else{
                if(!selectCell(m_cursor.m_cellidx))     //if an invalid cell was selected
                    drawCursorError();
            }
            break;
    }
}
/**************************************************************************************************/
bool TicTacToe::selectBoard(int position)
{
    if(m_bboard[position].getWinner() == NO_WINNER){
        m_currboardidx = static_cast<Position>(position);
        m_cursor.reposition(position, static_cast<int>(Position::LEFT_UP));
        //put this in the stack

        return true;
    }

    return false;
}
/**************************************************************************************************/
bool TicTacToe::selectCell(int position)
{
    if(!putPiece(position))
        return false;

    //put play in stack
    //
    updateWinner();

    if(m_bboard[position].getWinner() == NO_WINNER){
        m_currboardidx = static_cast<Position>(position);
        m_cursor.reposition(position, static_cast<int>(Position::LEFT_UP));
    }else{
        m_currboardidx = Position::NONE;
        m_cursor.reposition(static_cast<int>(Position::LEFT_UP));
    }

   changeTurn();

    return true;
}
/**************************************************************************************************/
bool TicTacToe::putPiece(int cellidx)
{
    if(m_currboardidx == Position::NONE) //there is no board selected
        return false;

    if(m_bboard[m_currboardidx][cellidx].piece != EMPTY) //the cell is already ocuppied
        return false;

    m_bboard[m_currboardidx][cellidx].piece = m_turn->getPiece();
    return true;
}
/**************************************************************************************************/
void TicTacToe::updateWinner()
{
    if(m_winner != NO_WINNER) //if there is already a winner there is no reason to check
        return;

    m_bboard.updateWinner();

    auto m_boards = m_bboard.m_boards;

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
void TicTacToe::draw() const
{
    al_clear_to_color(COLOR.BACKGROUND);
    m_bboard.draw(m_fonts.normal);

    drawGameInfo();

    drawBoardWinners();

    //just to know the limits
    ////////////////////////
    /*
    al_draw_rectangle(m_bboard.m_p0.x, m_bboard.m_p0.y, m_bboard.m_p1.x, m_bboard.m_p1.y, COLOR.WHITE, 3);

    for(const auto& board : m_bboard.m_boards)
        al_draw_rectangle(board.m_p0.x, board.m_p0.y, board.m_p1.x, board.m_p1.y, COLOR.BLUE, 3);

    float last = (m_dispdata.height - m_bboard.m_p1.y) * .8;
    al_draw_rectangle(m_bboard.m_p0.x, m_bboard.m_p1.y + 10, m_bboard.m_p1.x, m_bboard.m_p1.y + last, COLOR.WHITE, 3);
    */
    ////////////////////////

    m_cursor.draw(COLOR.PURPLE);

    al_flip_display();
}
/**************************************************************************************************/
void TicTacToe::drawGameInfo() const
{
    std::string player1 = m_player1.getName() + ": " + m_player1.getPiece();
    std::string player2 = m_player2.getName() + ": " + m_player2.getPiece();
    std::string currentPlayer = "Turno: " + m_turn->getName();
    float spaceFromBoard = 10;

    al_draw_text(m_fonts.normal, m_player1.getColor(),
                 m_bboard.m_p0.x, m_bboard.m_p1.y + spaceFromBoard,
                 ALLEGRO_ALIGN_LEFT, player1.c_str());

    al_draw_text(m_fonts.normal, m_player2.getColor(),
                 m_bboard.m_p1.x, m_bboard.m_p1.y + spaceFromBoard,
                 ALLEGRO_ALIGN_RIGHT, player2.c_str());

    float xcenter = (m_bboard.m_p0.x + m_bboard.m_p1.x) / 2.0;
    al_draw_text(m_fonts.normal, m_turn->getColor(),
                 xcenter, m_bboard.m_p1.y + spaceFromBoard,
                 ALLEGRO_ALIGN_CENTER, currentPlayer.c_str());
}
/**************************************************************************************************/
void TicTacToe::drawBoardWinners() const
{
    for(const auto& board : m_bboard.m_boards)
        board.drawWinner();

    m_bboard.drawWinner();
}
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
    std::array<std::string, 5> menuOption;
    menuOption[0] = "Jugar: Contra Computadora";
    menuOption[1] = "Jugar: Contra Otro Jugador";
    menuOption[2] = "Instrucciones";
    menuOption[3] = "Acerca de";
    menuOption[4] = "Salir";

    ALLEGRO_EVENT ev;
    while(ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE){
        al_clear_to_color(COLOR.BACKGROUND);

        //draws title
        txtpos = Point(width/2.0, 0);
        al_draw_text(m_fonts.title, COLOR.WHITE, txtpos.x, txtpos.y, ALLEGRO_ALIGN_CENTER, "Gato 81");

        //draws all menu options
        txtpos.y = height/3.0;
        for(const auto& option : menuOption){
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
                    if(menuOption[curridx] == "Jugar: Contra Computadora"){
                        reset("JUGADOR1", "X", "JUGADOR2", "O", Type::AI);
                        play();
                        std::cout << "Se terminó juego contra computadora" << std::endl;
                    }

                    else if(menuOption[curridx] == "Jugar: Contra Otro Jugador"){
                        reset("JUGADOR1", "X", "JUGADOR2", "O");
                        play();
                        std::cout << "Se terminó juego contra otro jugador" << std::endl;
                    }

                    else if(menuOption[curridx] == "Instrucciones"){
                        displayInstructions();
                    }

                    else if(menuOption[curridx] == "Acerca de"){
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
void TicTacToe::reset(std::string nameP1, std::string pieceP1, std::string nameP2, std::string pieceP2, Type typePlayerTwo /*= Type::HUMAN*/)
{
    m_winner = NO_WINNER;
    m_player1.setName(nameP1);
    m_player1.setPiece(pieceP1);

    m_player2.setName(nameP2);
    m_player2.setPiece(pieceP2);
    m_player2.setType(typePlayerTwo);

    m_cursor.reposition(Position::LEFT_UP);

    m_currboardidx = Position::NONE;
    m_turn = &m_player1;

    m_bboard.reset();

    al_flush_event_queue(m_eventQueue); //clean the event queue before playing

    //empy the stack of plays
}
/**************************************************************************************************/
void TicTacToe::drawCursorError() const
{
    draw();
    m_cursor.draw(COLOR.CURSOR_ERROR);
    al_flip_display();
    al_rest(1);
}
