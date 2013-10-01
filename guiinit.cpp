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

const DECL_FONT(fontProps,NULL,6,8);
piris::PFont fonty(fontProps);
const DECL_LABEL_PROPERTIES(label,20,250,"labelproste",piris::BLACK,piris::GREEN,NULL,fontProps);
const DECL_WIDGET_PROPERTIES(widget1,40,40,100,100,piris::GREEN);
const DECL_BUTTON_PROPERTIES(button,20,200,100,30,"tlacitko",piris::BLACK,piris::WHITE,NULL);

piris::PMaster * guiInit(piris::PPortingAbstract * port, int & size)
{
    piris::PMaster * mast;
    mast = new piris::PMaster(port);

    piris::PScreen * wid;
    wid = new piris::PScreen(mast);
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

    temp->setFocus();



    //button
    temp = new piris::PButton(button);
    temp->name = ("widget 3");

    wid->addChild(temp);

    //label
    temp = new piris::PLabel(label);

    wid->addChild(temp);

    i = temp->dataSize();




    wid->makeActive();

    size = i;
    return mast;

}
