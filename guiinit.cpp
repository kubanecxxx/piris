#include "porting.h"
#include "pkeyevent.h"
#include <QTimer>
#include "pwidget.h"
#include "pmaster.h"
#include "pscreen.h"
#include "qdebugprint.h"
#include "pbutton.h"
#include "pfont.h"
#include <QDebug>
#include "plabel.h"
#include "pcheckbox.h"

static const DECL_FONT(fontProps,NULL,6,8);
piris::PFont fonty(fontProps);
static const DECL_LABEL_PROPERTIES(label,20,250,"labelproste",piris::BLACK,piris::GREEN,NULL,fontProps);
static const DECL_WIDGET_PROPERTIES(widget1,20,20,80,80,piris::GREEN);
static const DECL_BUTTON_PROPERTIES(button,20,200,100,30,"tlacitko",piris::BLACK,piris::WHITE,NULL);

piris::PScreen * another_screen(piris::PPortingAbstract * port, int & size, piris::PMaster * mast);

piris::PMaster * guiInit(piris::PPortingAbstract * port, int & size)
{
    piris::PMaster * mast;
    mast = new piris::PMaster(port);

    piris::PScreen * wid;
    wid = new piris::PScreen(mast);
    wid->setColor(piris::PColor(235,234,233));
    wid->setFocusColor(piris::GREEN);
    wid->name = "screen1";
    wid->setFont(&fonty);
    int i;

    piris::PWidget * temp = new piris::PWidget(widget1);
    temp->name = ("widget 1");
    wid->addChild(temp);

    temp = new piris::PWidget();
    temp->setColor(piris::BLACK);
    temp->setX(80);
    temp->setY(80);
    temp->setWidth(100);
    temp->setHeight(100);
    temp->name = ("widget 2");
    i = temp->dataSize();
    wid->addChild(temp);

    piris::PWidget * t = temp;

    temp = new piris::PWidget();
    temp->setColor(piris::RED);
    temp->setX(30);
    temp->setY(30);
    temp->setWidth(10);
    temp->setHeight(10);
    temp->name = "subwidget";
    t->AddChild(temp);
    temp->setFocus();

    //button
    temp = new piris::PButton(button);
    temp->name = ("widget 3");
    wid->addChild(temp);


    //label
    temp = new piris::PLabel(label);
    temp->name = "label";

    wid->addChild(temp);

    i = temp->dataSize();



    //checkbox
    piris::PCheckBox * box = new piris::PCheckBox;
    box->name = "checkbox";
    box->setX(10);
    box->setY(230);
    box->setColor(piris::INVALID);
    box->setTextColor(piris::INVALID);

    wid->addChild(box);
    box->recomputeGeometry();


    wid->makeActive();

    size = i;

    int sze = 0;
    piris::PScreen * screen2 = another_screen(port,sze,mast);

    screen2->setFont(&fonty);
    screen2->setColor(piris::BLACK);
    screen2->setFocusColor(piris::BLUE);
    screen2->name = "screen2";
    screen2->makeActive();

    size = sze;
    return mast;
}

#include "pspecialspinbox.h"

void cb(piris::PKeyEvent * evt, piris::PSpecialSpinBox * spin)
{
    qlog("cb jaja");
}

const char * p[4] =
{
    "nebudu", "  to  ", " delat", "  kua "
};

const DECL_SPECIALSPINBOXWIDGET_PROPERTIES(spin1,20,50,"spin1",piris::WHITE,piris::INVALID,NULL,fontProps);
const DECL_SPECIALSPINBOX_PROPERTIES(spin1_p, 0,3,1, cb, p,4, NULL,1,5,0);
const DECL_SPECIALSPINBOXWIDGET_PROPERTIES(spin2,20,90,"spin2",piris::WHITE,piris::INVALID,NULL,fontProps);
const DECL_SPECIALSPINBOXWIDGET_PROPERTIES(spin3,20,150,"spin3",piris::WHITE,piris::INVALID,NULL,fontProps);

piris::PScreen * another_screen(piris::PPortingAbstract * port, int & size, piris::PMaster * m)
{
    piris::PScreen * screen = new piris::PScreen(m);
    piris::PSpecialSpinBox * s1 = new piris::PSpecialSpinBox(spin1_p,spin1,screen);
    s1->name = "spin1";
    piris::PSpecialSpinBox * s2 = new piris::PSpecialSpinBox(spin1_p,spin2,screen);
    s2->name = "spin2";
    piris::PSpecialSpinBox * s3 = new piris::PSpecialSpinBox(spin1_p,spin3,screen);
    s3->name = "spin3";

    s1->setFocus();
    size = screen->dataSize();

    return screen;
}
