#include "pscreen.h"
#include "pportingabstract.h"
#include "pwidget.h"
#include "pmaster.h"
#include "passert.h"
#include "ptouchevent.h"

namespace piris
{

PScreen::PScreen(PMaster *parent) :
		m(*new screen_props_t)
{
	construct(parent);
	m.color = BLACK;
	m.flags.w = 0;
	m.font = NULL;
	m.textColor = WHITE;
	m.focusColor = textColor().invert().rawData();
}

PScreen::PScreen(const screen_props_t &props, PMaster *parent) :
		m((screen_props_t &) props)
{
	construct(parent);
}

PScreen::PScreen(screen_props_t &props, PMaster *parent) :
		m(props)
{
	m.flags.b.ReadOnly = false;
	construct(parent);
}

void PScreen::construct(PMaster * parent)
{
	p = parent;
	child = NULL;
	focWidget = NULL;

#ifdef DRAWING_MODE_CHANGESONLY
	dirty = true;
#endif
}

void PScreen::draw(PPortingAbstract *port)
{
	passert(port, "port is not defined");
	passert(font(), "font is not defined");

#ifdef DRAWING_MODE_CHANGESONLY
	if (dirty)
	{
		port->fill(m.color);
	}

	PWidget * t = child;
	while (t)
	{
		if (dirty)
			t->dirty = true;
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
	dirty = false;

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

void PScreen::sendEvent(PTouchEvent *touch, PKeyEvent *key)
{
	if (touch->locked())
	{
		PWidget * wid = touch->locked();
		wid->processEvent(key, touch);
		return;
	}

	//focused widget ask first
	if (focusWidget() && focusWidget()->sendEvent(key, touch))
		return;

	PWidget * t = child;
	while (t)
	{
		if (t->sendEvent(key, touch))
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

#ifdef DRAWING_MODE_CHANGESONLY
	dirty = true;
#endif
}

void PScreen::setFocusWidget(PWidget *widget)
{
	passert(widget, "widget is NULL");
	focWidget = widget;

	qlog(QString("focused widget: %1").arg(widget->name));
}

size_t PScreen::dataSize() const
{
	uint16_t temp = sizeof(*this);
	if (!IsReadOnly())
		temp += sizeof(screen_props_t);

	PWidget * t = child;
	while (t)
	{
		temp += t->dataSize();
		t = t->nextSibling();
	}

	return temp;
}

bool PScreen::isActive() const
{
    return this == parent()->getActiveScreen();
}

}
