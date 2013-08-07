#include "pwidget.h"
#include "pportingabstract.h"
#include "passert.h"
#include "pkeyevent.h"
#include "ptouchevent.h"
#include "pmaster.h"
#include "pscreen.h"

namespace piris
{

PWidget::PWidget(PWidget * par)
{
    paren = par;

    p.x = 0;
    p.y = 0;
    p.w = 20;
    p.h = 20;
    p.backgroundColor = RED;
    p.flags.w = 0;
    setVisible(true);
    setEnabled(true);


    next = NULL;
    child = NULL;
    parScreen = NULL;

    //this widget will be automatically added as a parent child
    if (par)
        par->AddChild(this);
}

void PWidget::draw(PPortingAbstract *disp) const
{
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
bool PWidget::eventForMe(PKeyEvent *key, PTouchEvent *touch)
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

void PWidget::processEvent(PKeyEvent *key, PTouchEvent *touch)
{
    if (dragable())
    {
        touch->lock(this);
        qlog(QString("%1 dragging").arg(name));
    }

    //do something
    if (touch->event == PRESS)
        setFocus();

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

}
