
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
static const DECL_FONT(font8_p,NULL,8,8,1);
static const DECL_FONT(font16_p,NULL,16,16,2);
static piris::PFont font8(font8_p);
static piris::PFont font16(font16_p);

//main
static piris::PKeyEvent e;
static piris::PTouchEvent t;
static piris::PMaster mast(&e,&t);


//screen
static const DECL_SCREEN_PROPERTIES(main_screen,piris::BLACK,piris::WHITE,piris::BLUE,&font16,1);
static piris::PScreen main_screen(main_screen_p,&mast);

static const DECL_SPECIALSPINBOX_PROPERTIES(volume, 1,4,1, NULL, NULL,0, NULL,0,"Volume: %d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(volume,MARGIN,20,"",piris::RED,piris::INVALID,NULL,font16_p);
static piris::PSpecialSpinBox volume(volume_sp,volume_p,&main_screen);

static const DECL_SPECIALSPINBOX_PROPERTIES(gain, 1,4,1, NULL, NULL,0, NULL,0,"Gain:   %d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(gain,MARGIN,40,"",piris::GREEN,piris::INVALID,NULL,font16_p);
static piris::PSpecialSpinBox gain(gain_sp,gain_p,&main_screen);

//name,x,y,w,h,text,textColor,backgroundColor,font, flags
static const _DECL_WIDGET_PROPERTIES_DISABLED(mute,150,10,80,16,"Mute", piris::INVALID,piris::INVALID,NULL,0);
static piris::PCheckBox mute (mute_p, NULL);
static const _DECL_WIDGET_PROPERTIES_DISABLED(loop,150,30,80,16,"Loop", piris::INVALID,piris::INVALID,NULL,0);
static piris::PCheckBox loop (loop_p, NULL);
static const _DECL_WIDGET_PROPERTIES_DISABLED(high,150,50,80,16,"High", piris::INVALID,piris::INVALID,NULL,0);
static piris::PCheckBox high (high_p, NULL);

//name,x,y,text,textColor,backgroundColor,font,fontprops
#define H_OFFSET 80
static const DECL_LABEL_PROPERTIES(h_label, MARGIN, H_OFFSET, "Harmonizer properties",piris::INVALID,piris::INVALID,&font8,font8_p);
static piris::PLabel h_label(h_label_p);

static const DECL_SPECIALSPINBOX_PROPERTIES(harm_volume, 0,100,1, NULL, NULL,0, NULL,0,"Volume: %2u",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(harm_volume,MARGIN,H_OFFSET + 12,"",piris::INVALID,piris::INVALID,&font8,font8_p);
static piris::PSpecialSpinBox harm_volume(harm_volume_sp,harm_volume_p,&main_screen);

static const DECL_SPECIALSPINBOX_PROPERTIES(harm_harmony, 0,15,1, NULL, NULL,0, NULL,0,"Harmony: %d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(harm_harmony,MARGIN  ,H_OFFSET +24 ,"",piris::INVALID,piris::INVALID,&font8,font8_p);
static piris::PSpecialSpinBox harm_harmony(harm_harmony_sp,harm_harmony_p,&main_screen);

static const DECL_SPECIALSPINBOX_PROPERTIES(harm_mode, 0,15,1, NULL, NULL,0, NULL,0,"mode: %d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(harm_mode,MARGIN +100,H_OFFSET + 12,"",piris::INVALID,piris::INVALID,&font8,font8_p);
static piris::PSpecialSpinBox harm_mode(harm_mode_sp,harm_mode_p,&main_screen);

static const DECL_SPECIALSPINBOX_PROPERTIES(harm_key, 0,15,1, NULL, NULL,0, NULL,0,"key: %2d",NULL);
static const DECL_SPECIALSPINBOXWIDGET_PROPERTIES_DISABLED(harm_key,MARGIN + 100,H_OFFSET + 24,"",piris::INVALID,piris::INVALID,&font8,font8_p);
static piris::PSpecialSpinBox harm_key(harm_key_sp,harm_key_p,&main_screen);

//name,x,y,text,textColor,backgroundColor,font,fontprops
static DECL_LABEL_PROPERTIES(preset,MARGIN+ 25,150,"test",piris::WHITE, piris::INVALID,&font16, font16_p);
static piris::PLabel preset(preset_p);


piris::PMaster * mirekGuiInit(piris::PPortingAbstract * port, int & size)
{
    mast.setHW(port);

    main_screen.addChild(&mute);
    main_screen.addChild(&loop);
    main_screen.addChild(&high);
    main_screen.addChild(&h_label);
    main_screen.addChild(&preset);

    mute.setChecked(true);
    loop.setChecked(true);
    high.setChecked(true);

    main_screen.makeActive();

    preset.setText("trouba");


    size = main_screen.dataSize();
    return &mast;
}

