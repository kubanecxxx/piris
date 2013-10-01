#include "pcolor.h"

namespace piris
{

PColor::PColor()
{
    data = INVALID;
}

PColor::PColor(uint16_t r, uint16_t g, uint16_t b)
{
    set(r,g,b);
}

PColor::PColor(globalColors_t col)
{
    set(col);
}

void PColor::set(globalColors_t col)
{
    data = col;
}

void PColor::set(uint16_t r, uint16_t g, uint16_t b)
{
    setB(b);
    setR(r);
    setG(g);
}

void PColor::setB(uint16_t b)
{
   // b >>= 3;
    data &= 0b0000011111111111;
    data |= b << 11;
}

void PColor::setR(uint16_t r)
{
  //  r >>= 3;
    data &= 0b1111111111100000;
    data |= r & 0b11111;
}

void PColor::setG(uint16_t g)
{
   // g >>= 2;
    data &= 0b1111100000011111;
    data |= (g & 0b111111) << 5;
}

uint16_t PColor::getR() const
{
    return ((data & (0b11111 << 11 )) >> 11);
}

uint16_t PColor::getG() const
{
    return ((data & (0b111111 << 5)) >> 5);
}

uint16_t PColor::getB() const
{
    return (data & 0b11111);
}

PColor PColor::dark(uint8_t num, uint8_t denum) const
{
    PColor temp;
    temp.set(num * getR()/denum,num * getG()/denum,num  *getB()/denum);

    return temp;
}

PColor PColor::invert() const
{
    PColor temp ;
    temp.set(255-getR(),255-getG(),255-getB());
    return temp;
}

#ifdef QT_CORE_LIB
QColor PColor::get() const
{
    return QColor(getR()<<3,getG()<<2,getB()<<3);
}
#endif

}
