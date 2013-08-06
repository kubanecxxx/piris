#include "pwidget.h"
#include "pportingabstract.h"
#include "passert.h"
#include "pkeyevent.h"
#include "ptouchevent.h"

namespace piris
{

void PWidget::construct()
{
    p.x = 0;
    p.y = 0;
    p.w = 20;
    p.h = 20;
    p.backgroundColor = RED;
    p.flags.w = 0;

    next = NULL;
    child = NULL;
}

PWidget::PWidget(PWidget * par)
{
    construct();
    paren = par;

    //this widget will be automatically added as a parent child
    if (par)
        par->AddChild(this);
}

PWidget::PWidget(PMaster *par)
{
    construct();
    setAsScreen(true);
    paren = (PWidget*)par;
}

void PWidget::draw(PPortingAbstract *disp) const
{
    //draw root widget first
    pixel_t w,h,x,y;
    if (isScreen())
    {
        x=0; y = 0; w = disp->width(); h = disp->height();
    }
    else
    {
        passert(paren,"there is no parent");

        x = paren->x() + p.x; y = paren->y() + p.y;
        w = paren->x() + p.w; h = paren->y() + p.h;
    }
    disp->putRectangle(x,x+w,y,y+h, p.backgroundColor);

    //draw all children
    PWidget * temp = child;

    while(temp != NULL)
    {
        temp->draw(disp);
        temp = temp->next;
    }
}

void PWidget::AddChild(PWidget *child)
{
    passert(child, "there is no child");
    child->setParent(this);

    //first child
    if (this->child == NULL)
    {
        this->child = child;
        return;
    }

    //add another child
    this->child->AddSiblings(child);
}

void PWidget::AddSiblings(PWidget *brother)
{
    passert(brother, "invalid brother");
    //first brother
    if (next == NULL)
    {
        next = brother;
        return;
    }

    //find the last sister and append after her
    PWidget * temp = next;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = brother;
}

void PWidget::sendEvent(PKeyEvent *key, PTouchEvent *touch)
{
    //poprvé přinde od guička
    //widget to musi probublat ke správnymu synkovi
}

PWidget * PWidget::parent() const
{
    if (isScreen())
        return NULL;

    return paren;
}

PMaster * PWidget::parentMaster() const
{
    if (!isScreen())
        return NULL;

    return (PMaster*)paren;
}

}
