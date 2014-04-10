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

    typedef struct specialspinbox_p
    {
        int16_t low_lim;
        int16_t high_lim;
        int16_t step;
        cb_t cb;
        formater_t formater;
        text_t * text_table;
        uint8_t table_size;
        //formatting number
        uint8_t dot;
        uint8_t flags;
        uint8_t max_len;
        //second coordinates
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
        } b;
    } spinFlags;

public:
    //getters
    inline bool toggled() const {return spinFlags.b.Toggled;}
    inline bool circulation() const {return spinFlags.b.Circulation;}
    inline bool val() const {return value;}

    //setters
    inline void setCirculation(bool enabled) {spinFlags.b.Circulation = enabled;}
    void setValue(int16_t val);


    //1 - plus sign visible
    //2 - fill by zeros from left to max length
    static void formatNumber(int16_t val, char * output, uint8_t dot, uint8_t max_len, uint8_t flags);
    void formatNumber(char * output) const;
};

}


//static widget properties initializer for label
//fontprops is used for compute widget width and height
#define DECL_SPECIALSPINBOXWIDGET_PROPERTIES(name,x,y,text,textColor,backgroundColor,font,fontprops) \
    _DECL_WIDGET_PROPERTIES(name,x,y,\
    (fontprops.width *(sizeof(text)  - 1))\
    ,fontprops.height\
    ,text,textColor,backgroundColor,font,piris::selectable)

#define DECL_SPECIALSPINBOX_PROPERTIES(name,low_lim,high_lim,step,cb,text_table,size, formater, dot,max_len,flags) \
    piris::PSpecialSpinBox::specialspinbox_p name =  \
    { \
    low_lim, high_lim,step, cb , formater, text_table,size,dot,flags,max_len\
    }

#endif // PSPECIALSPINBOX_H
