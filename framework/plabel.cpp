#include "plabel.h"
#include "pfont.h"
#include "passert.h"
#include "pportingabstract.h"

namespace piris
{

PLabel::PLabel(const PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par)
{
}

PLabel::PLabel(PWidget *par):
    PWidget(par)
{
    setEnabled(false);
}

PLabel::PLabel(PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par)
{
    setEnabled(false);
}

void PLabel::recompute()
{
    passert(font(),"font is NULL");
    setWidth(font()->width()*strlen(text()));
    setHeight(font()->height());
}

void PLabel::draw(PPortingAbstract *disp) const
{
    passert(font(),"font is NULL");
    PWidget::draw(disp);
    disp->putText(text(),x(),y()+height(),*font(),textColor());
}

void PLabel::processEvent(PKeyEvent *, PTouchEvent *)
{

}

bool PLabel::eventForMe(const PKeyEvent *,const PTouchEvent *) const
{
    return false;
}

}
