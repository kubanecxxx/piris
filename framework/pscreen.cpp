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
    child(NULL)
{
    m.color = RED;
    m.focusColor = m.color.invert();
}

void PScreen::draw(PPortingAbstract *port)
{
    port->fill(m.color);

    PWidget * t = child;
    while(t)
    {
        t->draw(port);
        t = t->nextSibling();
    }
}

void  PScreen::sendEvent(PTouchEvent *touch, PKeyEvent *key)
{
    if (touch->locked())
    {
        PWidget * wid = touch->locked();
        wid->processEvent(key,touch);
        return;
    }

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
    uint16_t temp = sizeof(this);


    PWidget * t = child;
    while(t)
    {
        temp += t->dataSize();
        t = t->nextSibling();
    }

    return temp;
}

}
