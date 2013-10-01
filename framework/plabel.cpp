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
    wea();
    p.flags.b.Enable = 0;
}

PLabel::PLabel(PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par)
{
    wea();
    p.flags.b.Enable = 0;
}

void PLabel::recompute()
{
    wea();
    p.w = font()->width() * strlen(p.text);
    p.h = font()->height();
}

void PLabel::draw(PPortingAbstract *disp) const
{
    PWidget::draw(disp);
    disp->putText(text(),x(),y()+height(),*font(),textColor());
}

void PLabel::processEvent(PKeyEvent *, PTouchEvent *)
{

}

bool PLabel::eventForMe(PKeyEvent *, PTouchEvent *) const
{
    return false;
}

}
