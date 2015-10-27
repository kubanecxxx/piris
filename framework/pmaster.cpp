#include "pmaster.h"
#include "pportingabstract.h"
#include "passert.h"
#include "pscreen.h"
#include "pkeyevent.h"
#include "ptouchevent.h"

#ifdef PIRIS_USE_CALIBRATOR
#include "utils/touch_calibration.h"
#endif

namespace piris
{

PMaster::PMaster(PPortingAbstract *port):
    hw(port)
{
    passert(port,"port has to exist");
    port->fill(RED);
    activeScreen = NULL;

    key = new PKeyEvent;
    touch = new PTouchEvent;
}

PMaster::PMaster(PKeyEvent *k, PTouchEvent *t):
    hw(NULL),
    activeScreen(NULL),
    key(k),
    touch(t)
{

}

void PMaster::printScreen()
{
    passert(hw,"port has to exist");
    passert(activeScreen, "no screen is active");
    activeScreen->draw(hw);
}

void PMaster::setActiveScreen(PScreen *screen)
{
    passert(screen, "screen is NULL");
    activeScreen = screen;
}

void PMaster::main()
{
    //v tomhle vlákně bude periodicky pročitat všechny eventy a zpracovat je
    //až to jednou projde zavolá port->suspend
    //probrání si musi pořešit porting třeba přes nějaky přerušeni od tlačitek nebo od touche že má novy data
    //ještě je potřeba promyslet probrání při změně něčeho ne od usera ale přimo programem(hodiny..)

    //hodit do preprocesoru
    printScreen();

    PTouchEvent tch;
    PKeyEvent tmp;

    if (hw->readKeyEvent(&tmp) || hw->readTouchEvent(&tch))
    {
        if (!(tmp == *key) || !(tch == *touch))
        {
            //tch.xRelative = tch.x;
            //tch.yRelative = tch.y;
            *key = tmp;
            *touch = tch;
            passert(activeScreen, "no screen is active");
            activeScreen->sendEvent(&tch, &tmp);
        }
    }
}

#ifdef PIRIS_USE_CALIBRATOR
void PMaster::main(touchCalibration *calibrator,const touchCalibration::corrections_t *corrections, bool calibrate)
{
    if (calibrator && calibrate)
    {
        calibrator->loop();
    }
    else
    {
        printScreen();

        PTouchEvent tch;
        PKeyEvent tmp;

        if (hw->readKeyEvent(&tmp) || hw->readTouchEvent(&tch))
        {
            if (!(tmp == *key) || !(tch == *touch))
            {
                //tch.xRelative = tch.x;
                //tch.yRelative = tch.y;
                *key = tmp;
                *touch = tch;
                passert(activeScreen, "no screen is active");
                if (corrections)
                    touchCalibration::rawToPixels(&tch,corrections);
                activeScreen->sendEvent(&tch, &tmp);
            }
        }
    }
}
#endif

}
