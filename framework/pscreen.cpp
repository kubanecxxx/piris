#include "pscreen.h"
#include "pportingabstract.h"
#include "pwidget.h"
#include "pmaster.h"
#include "passert.h"
#include "ptouchevent.h"

namespace piris
{

PScreen::PScreen(PMaster *parent):
    p(parent),
    child(NULL),
    focWidget(NULL)
  #ifdef DRAWING_MODE_CHANGESONLY
  , dirty(true)
  #endif
{
    m.color = RED;
    m.focusColor = m.color.invert();
}

void PScreen::draw(PPortingAbstract *port)
{
#ifdef DRAWING_MODE_CHANGESONLY
    if (dirty)
    {
        port->fill(m.color);
        dirty = false;
    }

    PWidget * t = child;
    while(t)
    {
        if (t->dirty && t != focusWidget())
        {
            t->draw(port);
            t->dirty = false;
        }
        t = t->nextSibling();
    }

    //focused widget draw last
    if (focusWidget() && focusWidget()->dirty)
    {
        focusWidget()->draw(port);
        focusWidget()->dirty = false;
    }

#else
    port->fill(m.color);
    PWidget * t = child;
    while(t)
    {
        t->draw(port);
        t = t->nextSibling();
    }

    //focused widget draw last
    if (focusWidget())
        focusWidget()->draw(port);

#endif
}

void  PScreen::sendEvent(PTouchEvent *touch, PKeyEvent *key)
{
    if (touch->locked())
    {
        PWidget * wid = touch->locked();
        wid->processEvent(key,touch);
        return;
    }

    //focused widget ask first
    if (focusWidget() && focusWidget()->sendEvent(key,touch))
        return;

    PWidget * t = child;
    while(t)
    {
        if (t->sendEvent(key,touch))
            return;
        t = t->nextSibling();
    }
}

void PScreen::addChild(PWidget *widget)
{
    widget->setParent(NULL);
    widget->setParentScreen(this);

    if (child == NULL)
    {
        child = widget;
        return;
    }

    child->AddSiblings(widget);
}

void PScreen::makeActive()
{
    passert(p, "no parent master");
    p->setActiveScreen(this);
    qlog (QString ("Active screen: %1").arg(name));
}

void PScreen::setFocusWidget(PWidget *widget)
{
    passert(widget,"widget is NULL");
    focWidget = widget;

    qlog(QString("focused widget: %1").arg(widget->name));
}

size_t PScreen::dataSize() const
{
    uint16_t temp = sizeof(*this);


    PWidget * t = child;
    while(t)
    {
        temp += t->dataSize();
        t = t->nextSibling();
    }

    return temp;
}

}
