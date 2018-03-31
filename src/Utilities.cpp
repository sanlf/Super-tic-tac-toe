#include "../include/Utilities.h"

/**************************************************************************************************/
std::string readFile(const std::string& filePath)
{
    std::ifstream file;
    std::string text;
    std::string line;
    std::string endline = "\n";

    file.open(filePath);
    if(file.is_open()){
        while( (getline(file, line)) ){
            text += line + endline;
        }

        text += "\nPress ESC to return to the menu";
        file.close();
    }

    return text;
}
/**************************************************************************************************/
void handleReturnToMenu(ALLEGRO_EVENT_QUEUE* eventQueue)
{
    ALLEGRO_EVENT event;
    while(true){
        al_wait_for_event(eventQueue, &event);

        if(event.type == ALLEGRO_EVENT_KEY_UP)
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
    }
}
/**************************************************************************************************/

