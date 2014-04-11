#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "pspecialspinbox.h"

//screen
const DECL_SCREEN_PROPERTIES(main_screen,piris::BLACK,piris::WHITE,piris::BLUE,&font8,1);
piris::PScreen main_screen(main_screen_p,&mast);

//hours
const DECL_SPECIALSPINBOX_PROPERTIES(
        hours, 0,23,1, NULL, NULL,0, NULL,0,"%2u",
             NULL);
const DECL_SPECIALSPINBOXWIDGET_PROPERTIES(hours,MARGIN,10,"",piris::INVALID,piris::INVALID,NULL,font8_p);
piris::PSpecialSpinBox spin_hours(hours_sp,hours_p,&main_screen);

//minutes
const DECL_SPECIALSPINBOX_PROPERTIES(minutes, 0,59,1, NULL, NULL,0, NULL,0,"%.2u",NULL);
//const DECL_SPECIALSPINBOXWIDGET_PROPERTIES(minutes,26,10,"",piris::INVALID,piris::INVALID,NULL,font8_p);
const DECL_COMMON_SPECIALSPINBOXWIDGET_PROPERTIES(minutes,MARGIN+16,10,":",font8_p);
piris::PSpecialSpinBox spin_minutes(minutes_sp,minutes_p,&main_screen);

//days
const char * den_table[7] =
{
    "po", "ut","st","ct","pa","so","ne"
};
const DECL_COMMON_SPECIALSPINBOXWIDGET_PROPERTIES(day,MARGIN+90,10,"",font8_p);
const DECL_SPECIALSPINBOX_PROPERTIES(day, 0,6,1, NULL, den_table,7, NULL,0,"",NULL);
piris::PSpecialSpinBox spin_day(day_sp,day_p,&main_screen);

//program
const char * program_table[4] =
{
    "Vypnuto","Manual ","Voda   ","Topeni"
};
const DECL_SPECIALSPINBOXWIDGET_PROPERTIES(main_program,MARGIN,25,"",piris::INVALID,piris::INVALID,&font16,font16_p);
const DECL_SPECIALSPINBOX_PROPERTIES(main_program, 0,3,1, NULL, program_table,4, NULL,0,"",NULL);
DECL_SPECIAL_SPINBOX(main_program,&main_screen);

//chtena
const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(main_teplotaChtena,MARGIN+30,50,"",piris::INVALID,piris::INVALID,&font16,font16_p);
const DECL_SPECIALSPINBOX_PROPERTIES(main_teplotaChtena, 0,500,5, NULL, NULL,0, NULL,2,"%3d~",NULL);
DECL_SPECIAL_SPINBOX(main_teplotaChtena,&main_screen);

//teplota1
const DECL_SPECIALSPINBOXWIDGET_PROPERTIES(main_teplotaVoda,MARGIN,110,"Voda",piris::INVALID,piris::INVALID,&font16,font16_p);
const DECL_SPECIALSPINBOX_PROPERTIES(main_teplotaVoda, 0,500,5, NULL, NULL,0, NULL,2,"%3d~",NULL);
DECL_SPECIAL_SPINBOX(main_teplotaVoda,&main_screen);
//teplota2
const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(main_teplotaDoma,MARGIN,80,"Doma",piris::INVALID,piris::INVALID,&font16,font16_p);
const DECL_SPECIALSPINBOX_PROPERTIES(main_teplotaDoma, 0,500,5, NULL, NULL,0, NULL,2,"%3d~",NULL);
DECL_SPECIAL_SPINBOX(main_teplotaDoma,&main_screen);

void cb(piris::PKeyEvent *evt, piris::PSpecialSpinBox *spin);

//menu
const DECL_COMMON_SPECIALSPINBOXWIDGET_PROPERTIES(main_menu,MARGIN,140,"MENU",font8_p);
const DECL_SPECIALSPINBOX_PROPERTIES(main_menu, 0,6,1, cb, NULL,0, NULL,0,"",NULL);
piris::PSpecialSpinBox main_menu(main_menu_sp,main_menu_p,&main_screen);



//topim/netopim
const char * topi_table[2] =
{
    "Topim  ","Netopim"
};
const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(main_topi,60,140,"",piris::GREEN,piris::INVALID,NULL,font8_p);
const DECL_SPECIALSPINBOX_PROPERTIES(main_topi, 0,1,1, NULL, topi_table,2, NULL,0,"",NULL);
piris::PSpecialSpinBox main_topi(main_topi_sp,main_topi_p,&main_screen);


#endif // MAIN_SCREEN_H
