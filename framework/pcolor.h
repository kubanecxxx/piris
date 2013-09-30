#ifndef PCOLOR_H
#define PCOLOR_H

#include "ptypes.h"

#ifdef QT_CORE_LIB
#include <QColor>
#endif

namespace piris
{

class PColor
{
public:
    explicit PColor();
    explicit PColor(uint16_t r, uint16_t g, uint16_t b);
    PColor(globalColors_t col);
    inline void set(uint16_t r, uint16_t g, uint16_t b);
    inline void set(globalColors_t col);
    inline void setR(uint16_t r);
    inline void setG(uint16_t g);
    inline void setB(uint16_t b);
    inline uint16_t getR() const;
    inline uint16_t getG() const;
    inline uint16_t getB() const;
    inline uint16_t rawData() const {return (data);}
    PColor dark(uint8_t num, uint8_t denum) const;

#ifdef QT_CORE_LIB
    QColor get() const;
#endif

private:
    color_t data;
};
}

#endif // PCOLOR_H
