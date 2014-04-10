#include "pmaster.h"
#include "pportingabstract.h"
#include "passert.h"
#include "pscreen.h"
#include "pkeyevent.h"
#include "ptouchevent.h"

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

void PMaster::printScreen()
{
    if (activeScreen)
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
            activeScreen->sendEvent(touch, &tmp);
        }
    }
}

}
