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

void PLabel::draw(PPortingAbstract *disp) const
{
    PFont * f = fontDelegated();
    passert(f,"font is NULL");
    PWidget::draw(disp);
    disp->putText(text(),x(),y()+height(),*f,textColorDelegated());
}

void PLabel::processEvent(PKeyEvent *, PTouchEvent *)
{

}

bool PLabel::eventForMe(const PKeyEvent *,const PTouchEvent *) const
{
    return false;
}

/**
 * @brief PLabel::recomputeGeometry
 * method recompute widget geometry according to its text size and length
 * useable for labels checkboxes...
 */
void PLabel::recomputeGeometry()
{
    PFont * f = fontDelegated();
    passert(f,"font is NULL");
    setWidth(f->width()*strlen(text()));
    setHeight(f->height());
}


}
