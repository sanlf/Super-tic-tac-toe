#include <iostream> //for error streams
#include <memory> //for shared_ptr

#include <allegro5/allegro.h> //for most of allegro
#include <allegro5/allegro_font.h> //for allegro font
#include <allegro5/allegro_ttf.h> //for allegro true type font

#include "../include/TicTacToe.h" //for the game
#include "../include/GameFonts.h" //for various fonts the game uses

int main(int argc, char **argv)
{
    //***INITIALIZES ALLEGRO***********************************************************************/
    if(!al_init()){
        std::cerr << "Failed to initialize allegro!" << std::endl;
        return 1;
    }

    if(!al_init_primitives_addon()){
        std::cerr << "Failed to initialize addons!" << std::endl;
        return 1;
    }

    if(!al_init_font_addon()){
        std::cerr << "Failed to initialize font!" << std::endl;
        return 1;
    }

    if(!al_init_ttf_addon()){
        std::cerr << "Couldn't initialize true type font addon!" << std::endl;
        return 1;
    }
    //*********************************************************************************************/

    //***INITIALIZES DISPLAY, AND EVENTS***********************************************************/
    ALLEGRO_DISPLAY_MODE dispdata;
    al_get_display_mode(0, &dispdata);
    const float WIDTH = dispdata.width;
    const float HEIGHT = dispdata.height;

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    std::shared_ptr<ALLEGRO_DISPLAY> display(al_create_display(WIDTH, HEIGHT), al_destroy_display);
    if(display == nullptr){
        std::cerr << "Failed to create display!" << std::endl;
        return 1;
    }

    if(!al_install_keyboard()){
        std::cerr << "Couldn't initialize keyboard!" << std::endl;
        return 1;
    }

    std::shared_ptr<ALLEGRO_EVENT_QUEUE> eventQueue(al_create_event_queue(), al_destroy_event_queue);
    if(eventQueue == nullptr){
        std::cerr << "Failed to create event queue!" << std::endl;
        return 1;
    }

    std::shared_ptr<ALLEGRO_TIMER> timer(al_create_timer(1.0 / FPS), al_destroy_timer);
    if(timer == nullptr){
        std::cerr << "Failed to create timer!" << std::endl;
        return 1;
    }
    //*********************************************************************************************/

    //**REGISTERS THE EVENTS***********************************************************************/
    al_register_event_source(eventQueue.get(), al_get_display_event_source(display.get()));
    al_register_event_source(eventQueue.get(), al_get_timer_event_source(timer.get()));
    al_register_event_source(eventQueue.get(), al_get_keyboard_event_source());
    //*********************************************************************************************/

    //**CREATES THE FONTS**************************************************************************/
    //this calculates the area where the font will be, gets its square root and then its 30%
    float fontSize = 0.3 * sqrt( (WIDTH * HEIGHT) / (9*9) );
    std::shared_ptr<ALLEGRO_FONT> normalFont(al_load_font("TYPEWR__.TTF", fontSize, 0), al_destroy_font);
    if(normalFont == nullptr){
        std::cerr << "Couldn't load TYPEWR__.TTF!" << std::endl;
        return 1;
    }

    //this calculates the area where the font will be, gets its square root and then its 60%
    float titleFontSize = 0.6 * sqrt( (WIDTH * HEIGHT) / (30) );
    std::shared_ptr<ALLEGRO_FONT> titleFont(al_load_font("TYPEWR__.TTF", titleFontSize, 0), al_destroy_font);
    if(titleFont == nullptr){
        std::cerr << "Couldn't load TYPEWR__.TTF!" << std::endl;
        return 1;
    }

    float selectionFontSize = 0.5 * titleFontSize;
    std::shared_ptr<ALLEGRO_FONT> selectionFont(al_load_font("TYPEWR__.TTF", selectionFontSize, 0), al_destroy_font);
    if(selectionFont == nullptr){
        std::cerr << "Couldn't load TYPEWR__.TTF!" << std::endl;
        return 1;
    }

    float filesFontSize = 0.4 * selectionFontSize;
    std::shared_ptr<ALLEGRO_FONT> filesFont(al_load_font("TYPEWR__.TTF", filesFontSize, 0), al_destroy_font);
    if(filesFont == nullptr){
        std::cerr << "Couldn't load TYPEWR__.TTF!" << std::endl;
        return 1;
    }
    //*********************************************************************************************/

    //After everything is initialized and there were no errors, initialize the colors
    COLOR.initialize();

    GameFonts gamefonts(normalFont.get(), titleFont.get(), selectionFont.get(), filesFont.get(),
                        fontSize, titleFontSize, selectionFontSize, filesFontSize);

    TicTacToe game(display.get(), eventQueue.get(), timer.get(), gamefonts, dispdata);
    game.run();

    return 0;
}
