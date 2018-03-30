#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream> //for std::ifstream
#include <string> //for std::string
#include <allegro5/allegro.h> //for event queue

/**FUNCTIONS***************************************************************************************/
std::string readFile(const std::string& filePath);

void handleReturnToMenu(ALLEGRO_EVENT_QUEUE* eventQueue);
/**************************************************************************************************/

#endif // UTILITIES_H
