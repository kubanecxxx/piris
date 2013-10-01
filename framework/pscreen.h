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
class PFont;

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
       PColor focusColor;
       PFont * font;
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
    inline PColor focusColor() const {return m.focusColor;}
    inline PFont * font() const {return m.font;}

    //setters
    inline void setColor(PColor color) {m.color = color;}
    inline void setFocusColor(PColor color) {m.color = color;}
    inline void setFont(PFont * font) {m.font = font;}
    void setFocusWidget(PWidget * widget);
    size_t dataSize() const;

    friend class PMaster;
};

}

#endif // PSCREEN_H