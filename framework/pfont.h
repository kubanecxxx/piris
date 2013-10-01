#ifndef PFONT_H
#define PFONT_H

#include "ptypes.h"
#include "passert.h"

namespace piris
{

#define fontassert() passert(m.ro == 0,"readonly")

class PFont
{
public:
    typedef struct
    {
        const char * table;
        pixel_t height;
        pixel_t width;
        uint8_t ro;
    } properties_t;

    PFont(const char * table, pixel_t heigth, pixel_t width);
    PFont(properties_t & prop);
    PFont(const properties_t & prop);

public:
    inline const char * table() const {return m.table;}
    inline pixel_t height() const {return m.height;}
    inline pixel_t width() const {return m.width;}
    inline void setTable(const char *table) {fontassert();m.table = table;}
    inline void setWidth(pixel_t w) {fontassert();m.width = w;}
    inline void setHeight(pixel_t h) {fontassert();m.height = h;}

private:

    properties_t & m;

};


}

#define DECL_FONT(name,table,width,height) \
    piris::PFont::properties_t name = \
    {\
    table,height,width,1 \
    }\

#endif // PFONT_H
