#ifndef PWIDGET_H
#define PWIDGET_H

#include "pcolor.h"

#ifdef QT_CORE_LIB
#include <QString>
#endif

namespace piris
{

class PPortingAbstract;
class PKeyEvent;
class PTouchEvent;
class PMaster;

class PWidget
{
public:
    PWidget(PWidget * par = NULL);
    PWidget(PMaster * par);
#ifdef QT_CORE_LIB
    QString name;
#endif


public:

protected:
    //virtuální metody s událostma
    virtual void draw(PPortingAbstract * disp) const;
    virtual void sendEvent(PKeyEvent * key, PTouchEvent * touch);

private:
    PWidget * next;
    PWidget * child;
    PWidget * paren;
    inline void setParent(PWidget * par) {paren = par;}

protected:
    struct p
    {
        PColor backgroundColor;
        pixel_t x,y;
        pixel_t w,h;
        union
        {
            struct
            {
                uint8_t Enabled :1;
                uint8_t Screen  :1;
            } b;
            uint16_t w;
        } flags;

    } p;

    PWidget(const PWidget & other);

public:
    //getters
    inline pixel_t x() const {return p.x;}
    inline pixel_t y() const {return p.y;}
    inline pixel_t width() const {return p.w;}
    inline pixel_t height() const {return p.h;}
    inline PColor color() const {return p.backgroundColor;}
    inline PWidget * nextSibling() const {return next;}
    inline PWidget * firstChild() const {return child;}
    inline bool isScreen() const {return p.flags.b.Screen == 1;}
    PWidget * parent() const;
    PMaster * parentMaster() const;

    //setters
    inline void setX(pixel_t x) {p.x = x;}
    inline void setY(pixel_t y) {p.y = y;}
    inline void setWidth(pixel_t width) {p.w = width;}
    inline void setHeight(pixel_t height) {p.h = height;}
    inline void setColor(PColor col) {p.backgroundColor = col;}

    void AddChild(PWidget * child);
    void AddSiblings(PWidget * brother);

    friend class PMaster;

private:
    void construct();
    inline void setAsScreen(bool enabled) {p.flags.b.Screen = enabled;}
};


}
#endif // PWIDGET_H
