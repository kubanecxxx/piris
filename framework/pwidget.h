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
class PScreen;

class PWidget
{
public:
    PWidget(PWidget * par = 0);
#ifdef QT_CORE_LIB
    QString name;
#endif


public:

protected:
    //virtuální metody s událostma
    virtual void draw(PPortingAbstract * disp) const;
    virtual bool eventForMe(PKeyEvent * key, PTouchEvent * touch);
    virtual void processEvent(PKeyEvent * key, PTouchEvent * touch);

private:
    PWidget * next;
    PWidget * child;
    PWidget * paren;
    PScreen * parScreen;

    inline void setParent(PWidget * par) {paren = par;}
    inline void setParentScreen(PScreen * screen) {parScreen = screen;}


    void AddSiblings(PWidget * brother);
    bool sendEvent(PKeyEvent * key, PTouchEvent * touch);


    struct p
    {
        PColor backgroundColor;
        pixel_t x,y;
        pixel_t w,h;
        union
        {
            struct
            {

                uint8_t Enable :1;
                uint8_t Visible :1;
                uint8_t Dragable :1;
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
    PWidget * prevSibling() const;
    inline PWidget * firstChild() const {return child;}
    inline PWidget * parent() const {return paren;}
    inline PScreen * parentScreen() const {return parScreen;}
    inline bool visible() const {return p.flags.b.Visible;}
    inline bool enabled() const {return p.flags.b.Enable;}
    inline bool dragable() const {return p.flags.b.Dragable;}
    bool hasFocus() const;

    //setters
    inline void setX(pixel_t x) {p.x = x;}
    inline void setY(pixel_t y) {p.y = y;}
    inline void setWidth(pixel_t width) {p.w = width;}
    inline void setHeight(pixel_t height) {p.h = height;}
    inline void setColor(PColor col) {p.backgroundColor = col;}
    inline void setVisible(bool visible) {p.flags.b.Visible = visible;}
    inline void setEnabled(bool enable) {p.flags.b.Enable = enable;}
    inline void setDragable(bool dragable) {p.flags.b.Dragable = dragable;}
    void setFocus();

    void AddChild(PWidget * child);
    friend class PScreen;
};


}
#endif // PWIDGET_H
