#ifndef PSCREEN_H
#define PSCREEN_H

#include "ptypes.h"
#include "pcolor.h"

namespace piris
{

class PWidget;
class PMaster;
class PTouchEvent;
class PKeyEvent;
class PPortingAbstract;

class PScreen
{
public:
    PScreen(PMaster * parent = 0);
#ifdef QT_CORE_LIB
    QString name;
#endif

private:
    PScreen(const PScreen & other);
    PMaster * p;
    PWidget * child;
    PWidget * focWidget;

    struct m
    {
       PColor color;
    } m;

    void sendEvent(PTouchEvent * touch, PKeyEvent  * key);
    void draw(PPortingAbstract * port);

public:
    void addChild(PWidget * widget);
    void makeActive();

    //getters
    inline PMaster * parent() const {return p;}
    inline PColor color() const {return m.color;}
    inline PWidget * focusWidget() const {return focWidget;}
    inline PWidget * firstChild() const {return child;}

    //setters
    inline void setColor(PColor color) {m.color = color;}
    void setFocusWidget(PWidget * widget);

    friend class PMaster;
};

}

#endif // PSCREEN_H
