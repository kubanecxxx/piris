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

protected:
    struct p
    {
        PColor backgroundColor;
        pixel_t x,y;
        pixel_t w,h;
        pixel_t textSize;
        PColor textColor;
        const char * text;
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

private:
    PWidget(const PWidget & other);

public:
    //getters
    inline pixel_t x() const {return p.x;}
    pixel_t xLocal() const ;
    pixel_t yLocal() const ;
    inline pixel_t y() const {return p.y;}
    inline pixel_t width() const {return p.w;}
    inline pixel_t height() const {return p.h;}
    inline PColor color() const {return p.backgroundColor;}
    inline PColor textColor() const {return p.textColor;}
    inline PWidget * nextSibling() const {return next;}
    PWidget * prevSibling() const;
    inline PWidget * firstChild() const {return child;}
    inline PWidget * parent() const {return paren;}
    inline PScreen * parentScreen() const {return parScreen;}
    inline bool visible() const {return p.flags.b.Visible;}
    inline bool enabled() const {return p.flags.b.Enable;}
    inline bool dragable() const {return p.flags.b.Dragable;}
    inline pixel_t textSize() const {return p.textSize;}
    inline const char * text() const {return p.text;}
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
    inline void setTextSize(pixel_t size) {p.textSize = size;}
    inline void setText(const char * text) {p.text = text;}
    inline void setTextColor(PColor col) {p.textColor = col;}
    void setFocus();

    void AddChild(PWidget * child);
    friend class PScreen;
};


}
#endif // PWIDGET_H
