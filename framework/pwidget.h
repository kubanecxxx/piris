#ifndef PWIDGET_H
#define PWIDGET_H

#include "pcolor.h"

#ifdef QT_CORE_LIB
#include <QString>
#endif

#include "passert.h"
#define writeenableassert() passert(p.flags.b.ReadOnly == 0,"is readonly")
#define wea() writeenableassert()

namespace piris
{

class PFont;
class PPortingAbstract;
class PKeyEvent;
class PTouchEvent;
class PScreen;

class PWidget
{
public:

    typedef struct
    {
        PColor backgroundColor;
        pixel_t x,y;
        pixel_t w,h;
        PFont * font;
        PColor textColor;
        const char * text;
        union
        {
            struct
            {

                uint8_t Enable :1;
                uint8_t Visible :1;
                uint8_t Dragable :1;
                uint8_t ReadOnly :1;
            } b;
            uint16_t w;
        } flags;

    } PWidgetProperties_t;


    PWidget(PWidget * par = 0);
    PWidget(PWidgetProperties_t & prop, PWidget * par = NULL);
    PWidget(const PWidgetProperties_t & prop, PWidget * par = NULL);
#ifdef QT_CORE_LIB
    QString name;
#endif


public:


protected:
    //virtuální metody s událostma
    virtual void draw(PPortingAbstract * disp) const;
    virtual bool eventForMe(PKeyEvent * key, PTouchEvent * touch) const;
    virtual void processEvent(PKeyEvent * key, PTouchEvent * touch);

private:
    PWidget * next;
    PWidget * child;
    PWidget * paren;
    PScreen * parScreen;

    inline void setParent(PWidget * par) {paren = par;}
    inline void setParentScreen(PScreen * screen) {parScreen = screen;}
    void construct(PWidget * par);


    void AddSiblings(PWidget * brother);
    bool sendEvent(PKeyEvent * key, PTouchEvent * touch);

protected:
    PWidgetProperties_t & p;

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
    inline PFont * font() const {return p.font;}
    inline const char * text() const {return p.text;}
    virtual size_t dataSize() const;
    bool hasFocus() const;

    //setters
    inline void setX(pixel_t x) {wea() ;p.x = x;}
    inline void setY(pixel_t y) {wea();p.y = y;}
    inline void setWidth(pixel_t width) {wea();p.w = width;}
    inline void setHeight(pixel_t height) {wea();p.h = height;}
    inline void setColor(PColor col) {wea();p.backgroundColor = col;}
    inline void setVisible(bool visible) {wea();p.flags.b.Visible = visible;}
    inline void setEnabled(bool enable) {wea();p.flags.b.Enable = enable;}
    inline void setDragable(bool dragable) {wea();p.flags.b.Dragable = dragable;}
    inline void setFont(PFont * font) {wea();p.font = font;}
    inline void setText(const char * text) {wea();p.text = text;}
    inline void setTextColor(PColor col) {wea();p.textColor = col;}
    void setFocus();

    void AddChild(PWidget * child);
    friend class PScreen;
};

}


#define DECL_WIDGET_PROPERTIES(name,x,y,w,h,text,textColor,backgroundColor,font,enable) \
    _DECL_WIDGET_PROPERTIES(name,x,y,w,h,text,textColor,backgroundColor,font,enable,0,1,1)

#define _DECL_WIDGET_PROPERTIES(name,x,y,w,h,text,textColor,backgroundColor,font,enable,dragable,visible,readonly) \
    piris::PWidget::PWidgetProperties_t name =  \
    { \
    backgroundColor,x,y,w,h,font,textColor,text, {enable,visible,dragable,readonly} \
    }


#endif // PWIDGET_H
