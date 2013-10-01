#ifndef PLABEL_H
#define PLABEL_H

#include "pwidget.h"

namespace piris
{

class PLabel : public PWidget
{
public:
    PLabel(PWidget * par = NULL);
    PLabel(PWidgetProperties_t & props, PWidget *par = NULL);
    PLabel(const PWidgetProperties_t &props, PWidget *par = NULL);

    //must be called after setText by user
    void recompute();

protected:

    void draw(PPortingAbstract *disp) const;
    void processEvent(PKeyEvent *key, PTouchEvent *touch);
    bool eventForMe(PKeyEvent *key, PTouchEvent *touch) const;
};

//static widget properties initializer for label
//fontprops is used for compute widget width and height
#define DECL_LABEL_PROPERTIES(name,x,y,text,textColor,backgroundColor,font,fontprops) \
    _DECL_WIDGET_PROPERTIES(name,x,y,\
    (fontprops.width *(sizeof(text)  - 1))\
    ,fontprops.height\
    ,text,textColor,backgroundColor,font,0)

}

#endif // PLABEL_H
