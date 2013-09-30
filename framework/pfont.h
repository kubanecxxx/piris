#ifndef PFONT_H
#define PFONT_H

#include "ptypes.h"

namespace piris
{

class PFont
{
public:
    PFont(const char * table, pixel_t heigth, pixel_t width);

public:
    inline const char * table() const {return m.table;}
    inline pixel_t height() const {return m.height;}
    inline pixel_t width() const {return m.width;}
    inline void setTable(const char *table) {m.table = table;}
    inline void setWidth(pixel_t w) {m.width = w;}
    inline void setHeight(pixel_t h) {m.height = h;}

private:

    struct m {
        const char * table;
        pixel_t height;
        pixel_t width;
    } m;
};

}

#endif // PFONT_H
