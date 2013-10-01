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

    void recompute();

protected:
    void draw(PPortingAbstract *disp) const;
    void processEvent(PKeyEvent *key, PTouchEvent *touch);
    bool eventForMe(PKeyEvent *key, PTouchEvent *touch) const;
};

}

#endif // PLABEL_H
