#include "../include/Colors.h"

void Colors::initialize()
{
     BLACK              = al_map_rgb(0, 0, 0);
     WHITE              = al_map_rgb(255, 255, 255);
     RED                = al_map_rgb(255, 0, 0);
     GREEN              = al_map_rgb(0, 255, 0);
     BLUE               = al_map_rgb(0, 0, 255);
     PURPLE             = al_map_rgb(255, 0, 255);

     BACKGROUND         = BLACK;
     BOARD_COLOR        = WHITE;
     SMALL_BOARD_COLOR  = BLUE;
     CURSOR             = GREEN;
     CURSOR_P1          = GREEN;
     CURSOR_P2          = BLUE;
     CURSOR_ERROR       = RED;
}
//be cool and don't change the values of this GLOBAL VARIABLE
//initilize this only once and do it after initializing allegro
Colors COLOR;

