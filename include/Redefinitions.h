#ifndef REDEFINITIONS_H
#define REDEFINITIONS_H

#include <memory> //for std::unique_ptr
#include <allegro5/allegro.h> //for ALLEGRO_DISPLAY, ALLEGRO_EVENT_QUEUE, ALLEGRO_TIMER
#include <allegro5/allegro_font.h> //for allegro font

typedef std::unique_ptr<ALLEGRO_DISPLAY> DisplayPtr;
typedef std::unique_ptr<ALLEGRO_EVENT_QUEUE> EventQueuePtr;
typedef std::unique_ptr<ALLEGRO_TIMER> TimerPtr;
typedef std::unique_ptr<ALLEGRO_FONT> FontPtr;

#endif // REDEFINITIONS_H

