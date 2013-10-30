#include "pcheckbox.h"
#include "plabel.h"
#include "pfont.h"
#include "pportingabstract.h"

namespace piris
{

PCheckBox::PCheckBox(PWidget * par ):
    PWidget(par)
{
}

PCheckBox::PCheckBox(PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par)
{
}

PCheckBox::PCheckBox(const PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par)
{

}

void PCheckBox::draw(PPortingAbstract *disp) const
{
    PFont * f = fontDelegated();
    passert(f,"font is NULL");
    PWidget::draw(disp);
    disp->putRectangle(x(),x()+10,y()+1,y()+11,color().dark(2,1),true);
    //if pressed
    disp->putText(text(),x()+14,y()+height()-2,*f,textColor());
}

void PCheckBox::processEvent(PKeyEvent *key, PTouchEvent *touch)
{
    PWidget::processEvent(key,touch);

    //press
}

void PCheckBox::recomputeGeometry()
{
    PFont * f = fontDelegated();
    passert(f,"font is NULL");
    setWidth(f->width()*strlen(text())+15);
    setHeight(f->height()+4);
}

}
