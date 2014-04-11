#ifndef PSPECIALSPINBOX_H
#define PSPECIALSPINBOX_H

#include "pwidget.h"

namespace piris
{

class PKeyEvent;
class PSpecialSpinBox;

class PSpecialSpinBox : public PWidget
{
public:
    typedef void (*cb_t)(piris::PKeyEvent * evt, piris::PSpecialSpinBox * spin);
    typedef void (*formater_t)(int16_t value, char * output);
    typedef const char * text_t;

    typedef struct secondCoor_t
    {
        pixel_t x;
        pixel_t y;
    } secondCoor_t;

    typedef struct specialspinbox_p
    {
        int16_t low_lim;
        int16_t high_lim;
        int16_t step;
        cb_t cb;
        formater_t formater;
        const text_t * text_table;
        uint8_t table_size;
        //formatting number
        uint8_t dot;
        const char * fmt;
        //second coordinates
        const secondCoor_t * sec;
    } specialspinbox_p;

    PSpecialSpinBox(const specialspinbox_p & p, const PWidgetProperties_t & props, PScreen * screen = NULL);
    size_t dataSize() const {return sizeof(*this);}


protected:
    virtual void draw(PPortingAbstract *disp) const;
    virtual void processEvent(PKeyEvent *key, PTouchEvent *touch);

private:
    const specialspinbox_p & sp;
    int16_t value;

    void putItem(PPortingAbstract * disp,const char * value,  pixel_t x, pixel_t y, PColor color1, PColor color2) const;

    union
    {
        uint8_t w;
        struct
        {
            bool Toggled :1;
            bool Circulation: 1;
         //   bool showValue: 1;
            bool toggleable : 1;
            bool hide:1;
        } b;
    } spinFlags;

public:
    //getters
    inline bool toggled() const {return spinFlags.b.Toggled;}
    inline bool circulation() const {return spinFlags.b.Circulation;}
    inline bool val() const {return value;}
    inline bool toggleable() const {return spinFlags.b.toggleable;}
    //inline bool showvalue() const {return spinFlags.b.showValue;}
    inline bool hidden() const {return spinFlags.b.hide;}

    //setters
    inline void setCirculation(bool enabled) {spinFlags.b.Circulation = enabled;}
    inline void setToggleable(bool enabled) {spinFlags.b.toggleable = enabled;}
    //inline void setShowValue(bool enabled) {spinFlags.b.showValue = enabled;}
    inline void setHidden(bool enabled) {spinFlags.b.hide = enabled;}

    void setValue(int16_t val);

    void formatNumber(char * output) const;

};

}


//static widget properties initializer for label
//fontprops is used for compute widget width and height
#define DECL_SPECIALSPINBOXWIDGET_PROPERTIES(name,x,y,text,textColor,backgroundColor,font,fontprops) \
    _DECL_WIDGET_PROPERTIES(name,x,y,\
    ((piris::pixel_t)(fontprops.width *((sizeof(text)  - 1))))\
    ,fontprops.height\
    ,text,textColor,backgroundColor,font,piris::selectable)

#define DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(name,x,y,text,textColor,backgroundColor,font,fontprops) \
    _DECL_WIDGET_PROPERTIES_DISABLED(name,x,y,\
    ((piris::pixel_t)(fontprops.width *((sizeof(text)  - 1))))\
    ,fontprops.height\
    ,text,textColor,backgroundColor,font,piris::selectable)

#define DECL_COMMON_SPECIALSPINBOXWIDGET_PROPERTIES(name,x,y,text,fontprops) \
    DECL_SPECIALSPINBOXWIDGET_PROPERTIES(name,x,y,text,piris::INVALID,piris::INVALID,NULL,fontprops)

#define DECL_SPECIALSPINBOX_PROPERTIES(name,low_lim,high_lim,step,cb,text_table,size, formater, dot,fmt, sec_coordinates) \
    piris::PSpecialSpinBox::specialspinbox_p name##_sp =  \
    { \
    low_lim, high_lim,step, cb , formater, text_table,size,dot,fmt, sec_coordinates\
    }

#define DECL_SPECIAL_SPINBOX_SECOND_COORDINATES(name, x,y ) \
    piris::PSpecialSpinBox::secondCoor_t name = \
    {\
    x,y\
    }

#define DECL_SPECIAL_SPINBOX(name,parent) \
    piris::PSpecialSpinBox name(name##_sp,name##_p,parent)

#endif // PSPECIALSPINBOX_H
