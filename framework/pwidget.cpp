#include "pwidget.h"
#include "pportingabstract.h"
#include "passert.h"
#include "pkeyevent.h"
#include "ptouchevent.h"
#include "pmaster.h"
#include "pscreen.h"

namespace piris
{

PWidget::PWidget(PWidgetProperties_t &prop, PWidget *par):
    p(prop)
{
    p.flags.b.ReadOnly = 0;
    p.flags.b.IsContainer = 1;
    construct(par);
}

PWidget::PWidget(const PWidgetProperties_t &prop, PWidget *par):
    p((PWidgetProperties_t &) prop)
{
    construct(par);
}

PWidget::PWidget(PWidget * par):
    p(*new PWidgetProperties_t)
{
    p.x = 0;
    p.y = 0;
    p.w = 20;
    p.h = 20;
    p.textColor = BLACK;
    //auto delegating up to screen font
    p.font = NULL;
    p.text = NULL;
    p.backgroundColor = RED;
    p.flags.w = 0;
    p.flags.b.ReadOnly = 0;
    p.flags.b.IsContainer = 1;
    setVisible(true);
    setEnabled(true);

    construct(par);
}

void PWidget::construct(PWidget *par)
{
    paren = par;
    next = NULL;
    child = NULL;
    parScreen = NULL;

    //this widget will be automatically added as a parent child
    if (par)
        par->AddChild(this);
}

void PWidget::draw(PPortingAbstract *disp) const
{
    passert(parScreen, "no parent screen yet");
    if (!visible())
        return;

    //draw root widget first
    pixel_t w=0,h=0,x=0,y=0;

    if (paren)
    {
        w = x = paren->x();
        h = y = paren->y();
    }

    x += p.x; y += p.y;
    w += p.w; h += p.h;


    //delegate color from parent widget or screen
    PColor tmp = p.backgroundColor;
    if (!tmp.isValid())
    {
        //delegate up to screen
        PWidget * wid = parent();
        while(wid)
        {
            if (wid->color().isValid())
            {
                tmp = wid->color();
                break;
            }
        }
        //no widget has valid color take color from screen
        if (!tmp.isValid())
            tmp = parentScreen()->color();
    }

    disp->putRectangle(x,x+w,y,y+h, tmp);

    //draw all children
    PWidget * temp = child;

    while(temp != NULL)
    {
        temp->draw(disp);
        temp = temp->next;
    }

    if (hasFocus())
    {
        disp->putRectangleEmpty(x,x+w,y,y+w,parentScreen()->focusColor());
        disp->putRectangleEmpty(x+1,x+w-1,y+1,y+h-1,parentScreen()->focusColor());
    }
}

pixel_t PWidget::xLocal() const
{
    pixel_t x=0;

    if (paren)
    {
        x = paren->x();
    }

    x += p.x;

    return x;
}

pixel_t PWidget::yLocal() const
{

    pixel_t y=0;

    if (paren)
    {
        y = paren->y();
    }

    y += p.y;

    return y;
}


void PWidget::AddChild(PWidget *child)
{
    passert(p.flags.b.IsContainer == 0, "I am not a container");
    passert(child, "there is no child");
    passert(parScreen, "no parent screen yet");

    child->setParent(this);
    child->setParentScreen(parScreen);

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
    passert(parScreen, "no parent screen yet");

    brother->setParent(parent());

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

    brother->setParentScreen(parScreen);
}

/**
 * @brief PWidget::sendEvent zajištuje jenom rekurzivní volání subwidgetů
 * @param key
 * @param touch
 * @return true pokud se našel widget kterej to zpracoval
 */
bool PWidget::sendEvent(PKeyEvent *key, PTouchEvent *touch)
{
    //poprvé přinde od screenu a musi to probublat dál
    //přepočitat souřadnice na relativní když se to bude posilat dál
    //prvni projet děti, když budou false pak teprve volat na sebe

    if (!visible() || !enabled())
        return false;

    PWidget * t = child;

    while(t)
    {
        touch->xRelative = x() + touch->xRelative;
        touch->yRelative = y() + touch->yRelative;
        bool ok;
        ok = t->sendEvent(key,touch);
        if (ok)
            return true;
        t = t->next;
    }

    bool ok = eventForMe(key,touch);
    if (ok)
        processEvent(key,touch);

    return ok;
}

/**
 * @brief PWidget::eventForMe rozhodne že je to pro něho
 * @param key
 * @param touch
 * @return true pokud ho vzal
 */
bool PWidget::eventForMe(PKeyEvent *key, PTouchEvent *touch) const
{
    //if not for me return false

    //key event
    if (hasFocus() && key->key)
    {
        qlog(QString("%1: key %2, %3").arg(name).arg(key->key).arg(key->event));
        return true;
    }

    //touch event
    if (touch->event && touch->xRelative >= x() && touch->xRelative <= x() + width() &&
            touch->yRelative >= y() && touch->yRelative <= y() + height())
    {
        qlog(QString("%1: touch %2;%3 ; %4").arg(name).arg(touch->xRelative).
             arg(touch->yRelative).arg(touch->event));

        return true;
    }

    return false;
}

void PWidget::processEvent(PKeyEvent *key,  PTouchEvent *touch)
{
    if (dragable())
    {
        touch->lock(this);
        qlog(QString("%1 dragging").arg(name));
    }

    //do something
    if (touch->event == PRESS)
        setFocus();

    standardNextPrev(key);

    if (touch->event == RELEASE && touch->locked())
    {
        touch->unlock();
        qlog(QString("%1 dropped").arg(name));
    }

}

PWidget * PWidget::prevSibling() const
{
    PWidget * temp = 0;
    if (paren)
    {
        temp = paren->firstChild();
    }
    else
    {
        passert(parScreen, "no parent screen");
        temp = parentScreen()->firstChild();
    }

    while(temp->nextSibling() != this)
    {
        temp = temp->nextSibling();
        if (temp == 0)
            return temp;
    }

    return temp;
}

bool PWidget::hasFocus() const
{
    passert(parScreen, "no parent screen");
    return (parScreen->focusWidget() == this);
}

void PWidget::setFocus()
{
    passert(parScreen, "no parent screen");
    parScreen->setFocusWidget(this);

}

size_t PWidget::dataSize() const
{
    //draw all children
    PWidget * temp = child;
    uint16_t size = sizeof(*this);
    if (!p.flags.b.ReadOnly)
        size += sizeof(PWidgetProperties_t);

    while(temp != NULL)
    {
        size += temp->dataSize();
    }

    return size;
}

PFont * PWidget::font() const
{
    if (p.font)
        return p.font;

    //delegate up to screen
    PWidget * wid = parent();
    while(wid)
    {
        if (wid->font())
        {
            return wid->font();
        }
    }
    //no widget has valid font so take font from screen
    return  parentScreen()->font();
}

/**
 * @brief PWidget::standardNextPrev
 * standard selecting previous/next widget by up/down key
 * @param key
 */
void PWidget::standardNextPrev(const PKeyEvent * key)
{
    PWidget * p = 0;
    if (key->event == PRESSED)
    {
        if (key->key == kUP)
        {
           p = prevSibling();
           while(p != NULL && !(p->visible() && p->enabled()))
               p = p->prevSibling();
        }
        if (key->key == kDOWN)
        {
            p = nextSibling();
            while(p != NULL &&!(p->visible() && p->enabled()))
                p = p->nextSibling();
        }

        if (p)
            p->setFocus();
    }
}

}
