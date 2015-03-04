#ifndef PSCREEN_H
#define PSCREEN_H

#include "ptypes.h"
#include "pcolor.h"
#include "passert.h"

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
    typedef struct screen_props_t
    {
        color_t color;
        color_t textColor;
        color_t focusColor;
        PFont * font;
        union
        {
            uint16_t w;
            struct
            {
                bool inCircles :1;
                bool res1 :1;
                bool res2:1;
                bool ReadOnly :1;
            } b;
        } flags;
    } screen_props_t;

    PScreen(PMaster * parent = 0);
    PScreen(screen_props_t & props, PMaster * parent = NULL);
    PScreen(const screen_props_t & props,PMaster * parent = NULL);
#ifdef QT_CORE_LIB
    QString name;
#endif

private:
    PScreen(const PScreen & other);
    PMaster * p;
    PWidget * child;
    PWidget * focWidget;

    void construct(PMaster * parent);

#ifdef DRAWING_MODE_CHANGESONLY
public:
    bool dirty;
private:
#endif
    screen_props_t & m;

    void sendEvent(PTouchEvent * touch, PKeyEvent  * key);
    void draw(PPortingAbstract * port);

public:
    void addChild(PWidget * widget);
    void makeActive();

    //getters
    inline PMaster * parent() const {return p;}
    inline PColor color() const {return PColor(m.color);}
    inline PColor textColor() const {return m.textColor;}
    inline PWidget * focusWidget() const {return focWidget;}
    inline PWidget * firstChild() const {return child;}
    inline PColor focusColor() const {return m.focusColor;}
    inline PFont * font() const {return m.font;}
    inline bool inCircles() const {return m.flags.b.inCircles;}

    //setters
    inline void setColor(PColor color) {wea();m.color = color.rawData();}
    inline void setFocusColor(PColor color) {wea();m.focusColor = color.rawData();}
    inline void setFont(PFont * font) {wea();m.font = font;}
    inline void setTextColor(PColor color) {wea();m.textColor = color.rawData();}
    inline void setInCircles(bool enabled) {wea(); m.flags.b.inCircles = enabled;}
    inline bool IsReadOnly() const {return m.flags.b.ReadOnly;}
    void setFocusWidget(PWidget * widget);
    size_t dataSize() const;
    bool isActive() const ;

    friend class PMaster;
};
}

#define DECL_SCREEN_PROPERTIES(name,background_color,text_color,focus_background_color,font, flags) \
    piris::PScreen::screen_props_t name##_p = \
    {\
    background_color, text_color,focus_background_color,font,flags | piris::readonly\
    }

#endif // PSCREEN_H
