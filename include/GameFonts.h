#ifndef GAMEFONTS_H
#define GAMEFONTS_H

//Simple coordinate structure. Has x and y.
struct GameFonts{
    ALLEGRO_FONT* normal;
    ALLEGRO_FONT* title;
    ALLEGRO_FONT* selection;
    ALLEGRO_FONT* files;
    
    float normalSize;
    float titleSize;
    float selectionSize;
    float filesSize;

    GameFonts(ALLEGRO_FONT* normal,
              ALLEGRO_FONT* title,
              ALLEGRO_FONT* selection,
              ALLEGRO_FONT* files,
              float normalSize       = 0,
              float titleSize        = 0,
              float selectionSize    = 0,
              float filesSize        = 0)
    {
        this->normal            = normal;
        this->title             = title;
        this->selection         = selection;
        this->files             = files;
        this->normalSize        = normalSize;
        this->titleSize         = titleSize;
        this->selectionSize     = selectionSize;
        this->filesSize         = filesSize;
    }
                            
};

#endif // GAMEFONTS_H

