#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

enum Position{LEFT_UP, CENTER_UP, RIGHT_UP,
                    LEFT_CENTER, CENTER_CENTER, RIGHT_CENTER,
                    LEFT_DOWN, CENTER_DOWN, RIGHT_DOWN,
                    LEFT = LEFT_CENTER, CENTER = CENTER_CENTER, RIGHT = RIGHT_CENTER,
                    UP, DOWN,
                    NONE = -1};

enum class Type{HUMAN, AI};
enum class Mode{BOARD, CELL};

#endif //ENUMERATIONS_H

