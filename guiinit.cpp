#include "porting.h"
#include "pkeyevent.h"
#include <QTimer>
#include "pwidget.h"
#include "pmaster.h"
#include "pscreen.h"
#include "qdebugprint.h"
#include "pbutton.h"
#include "pfont.h"
#include "ptouchevent.h"
#include <QDebug>
#include "plabel.h"
#include "pcheckbox.h"
#include "pspecialspinbox.h"

#define MARGIN  5
//fonts
static const DECL_FONT(font8_p,NULL,8,8);
static const DECL_FONT(font16_p,NULL,16,16);
piris::PFont font8(font8_p);
piris::PFont font16(font16_p);

//main
piris::PKeyEvent e;
piris::PTouchEvent t;
piris::PMaster mast(&e,&t);

/*********************************************************
 * main screen object declaration
 *********************************************************/
#include "main_screen.h"

/*********************************************************
 * menu screen
 *********************************************************/
#include "menu_screen.h"



piris::PMaster * guiInit(piris::PPortingAbstract * port, int & size)
{
    spin_hours.name = "hodiny";
    spin_minutes.name = "minuty";
    spin_day.name = "day";
    main_menu.name = "menu";
    main_screen.name = "main";
    main_topi.name = "topi";


    main_menu.setToggleable(false);
    menu_topeni.setToggleable(false);
    menu_voda.setToggleable(false);
    menu_zpet.setToggleable(false);

    menu_screen.name = "menu";


    main_screen.makeActive();
    main_screen.setFocusWidget(&spin_hours);

    menu_screen.setFocusWidget(&menu_topeni);


    mast.setHW(port);
    size = main_screen.dataSize();
    size += menu_screen.dataSize();
    return &mast;
}

void cb(piris::PKeyEvent *, piris::PSpecialSpinBox *)
{
    menu_screen.makeActive();
    menu_screen.dirty = true;
}

void cb_enterMain(piris::PKeyEvent *, piris::PSpecialSpinBox *)
{
    main_screen.makeActive();
    main_screen.dirty = true;
}

void cb_enterTopeni (piris::PKeyEvent *, piris::PSpecialSpinBox *)
{

}

void cb_enterVoda(piris::PKeyEvent *, piris::PSpecialSpinBox *)
{

}




