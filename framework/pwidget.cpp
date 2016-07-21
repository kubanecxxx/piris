#include "pwidget.h"
#include "pportingabstract.h"
#include "passert.h"
#include "pkeyevent.h"
#include "ptouchevent.h"
#include "pmaster.h"
#include "pscreen.h"
#include <strings.h>
#include "pfont.h"

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
    p.flags.b.Selectable = 1;
    p.flags.b.IsContainer = 1;
    setVisible(true);
    setEnabled(true);
    setText("text");

    construct(par);
}

void PWidget::construct(PWidget *par)
{
    paren = par;
    next = NULL;
    child = NULL;
    parScreen = NULL;

#ifdef DRAWING_MODE_CHANGESONLY
    dirty = true;
#endif

    //this widget will be automatically added as a parent child
    if (par)
        par->AddChild(this);
}

void PWidget::draw(PPortingAbstract *disp) const
{
    passert(parScreen, "no parent screen yet");
#ifdef DRAWING_MODE_CHANGESONLY
    //draw root widget first
    pixel_t w=0,h=0,x=0,y=0;


    x = xGlobal(); y = yGlobal();
    w = p.w; h = p.h;


    //delegate color from parent widget or screen
    PColor tmp = backgroundColorDelegated();
    disp->putRectangle(x,x+w,y,y+h, tmp,true);
#endif
    if (!visible())
        return;

#ifndef DRAWING_MODE_CHANGESONLY
    //draw root widget first
    pixel_t w=0,h=0,x=0,y=0;


    x = xGlobal(); y = yGlobal();
    w = p.w; h = p.h;


    //delegate color from parent widget or screen
    PColor tmp = backgroundColorDelegated();
    disp->putRectangle(x,x+w,y,y+h, tmp,true);
#endif
    //draw all children
    PWidget * temp = child;

    while(temp != NULL)
    {
        temp->draw(disp);
        temp = temp->next;
    }

    if (hasFocus())
    {
        disp->putRectangle(x,x+w,y,y+h,parentScreen()->focusColor());
        disp->putRectangle(x+1,x+w-1,y+1,y+h-1,parentScreen()->focusColor());
    }
}

pixel_t PWidget::xGlobal() const
{
    pixel_t x=0;

    if (paren)
    {
        x = paren->x();
    }

    x += p.x;

    return x;
}

pixel_t PWidget::yGlobal() const
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
    passert(IsContainer(), "I am not a container");
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
bool PWidget::eventForMe(const PKeyEvent *key,const PTouchEvent *touch) const
{
    //if not for me return false

    //key event
    if (hasFocus() && key->key)
    {
        qlog(QString("%1: key %2, %3").arg(name).arg(key->key).arg(key->event));
        return true;
    }

    pixel_t x = xGlobal();
    pixel_t y = yGlobal();

    //touch event
    if (touch->event && touch->x >= x && touch->x <= x + width() &&
            touch->y >= y && touch->y <= y + height())
    {
        qlog(QString("%1: touch %2;%3 ; %4").arg(name).arg(touch->x).
             arg(touch->y).arg(touch->event));

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

PWidget * PWidget::nextSiblingCircle() const
{
    if (nextSibling())
        return nextSibling();

    if (paren)
        return paren->firstChild();

    passert(parScreen, "no parent screen");
    return parScreen->firstChild();
}

PWidget * PWidget::prevSiblingCircle() const
{
    PWidget * p = prevSibling();
    if (p)
        return p;

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

    while(temp->nextSibling())
    {
        temp = temp->nextSibling();
    }
    return temp;
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

    #ifdef QT_CORE_LIB
    size -= sizeof(name);
    #endif

    while(temp != NULL)
    {
        size += temp->dataSize();
    }

    return size;
}

/**
 * @brief PWidget::standardNextPrev
 * standard selecting previous/next widget by up/down key
 * @param key
 */
void PWidget::standardNextPrev(const PKeyEvent * key)
{
    PWidget * p = 0;
    bool b = parentScreen()->inCircles();
    typedef PWidget* (PWidget::*f)() const;
    f fc = NULL;

    if (key->event == PRESSED)
    {
        if (key->key == kUP)
        {
            if (b)
                fc = &PWidget::prevSiblingCircle;
            else
                fc = &PWidget::prevSibling;
        }
        if (key->key == kDOWN)
        {
            if (b)
                fc = &PWidget::nextSiblingCircle;
            else
                fc = &PWidget::nextSibling;
        }
        if (!fc)
            return;

        p = (this->*fc)();
        while(p != NULL && !(p->visible() && p->selectable() && p->enabled()))
            p = (p->*fc)();

        if (p)
        {
            p->setFocus();
#ifdef DRAWING_MODE_CHANGESONLY
            dirty = true;
            p->dirty = true;
#endif
        }
    }
}

/**
 * @brief PWidget::fontDelegated
 * @return return delegated font up to screen
 */
PFont * PWidget::fontDelegated() const
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
        wid = wid->parent();
    }
    //no widget has valid font so take font from screen
    passert(parentScreen(),"screen is null");

    return  parentScreen()->font();
}

PColor PWidget::textColorDelegated() const
{
    if (textColor().isValid())
        return textColor();

    //delegate up to screen
    PWidget * wid = parent();
    while(wid)
    {
        if (wid->textColor().isValid())
        {
            return wid->textColor();
        }
        wid = wid->parent();
    }

    //no widget has valid font so take font from screen
    passert(parentScreen(),"screen is null");
    return  parentScreen()->textColor();
}

PColor PWidget::backgroundColorDelegated() const
{
    if (color().isValid())
        return color();

    //delegate up to screen
    PWidget * wid = parent();
    while(wid)
    {
        if (wid->color().isValid())
        {
            return wid->color();
        }
        wid = wid->parent();
    }

    //no widget has valid font so take font from screen
    passert(parentScreen(),"screen is null");
    return  parentScreen()->color();
}

}
