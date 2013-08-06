#include "pmaster.h"
#include "pportingabstract.h"
#include "passert.h"
#include "pwidget.h"

namespace piris
{

PMaster::PMaster(PPortingAbstract *port):
    hw(port)
{
    passert(port,"port has to exist");
    port->fill(RED);
    activeScreen = NULL;
}

void PMaster::printScreen()
{
    if (activeScreen)
        activeScreen->draw(hw);
}

void PMaster::setActiveScreen(PWidget *screen)
{
    passert(screen, "PWidget is NULL");
    bool ok = screen->isScreen();
    passert(ok, "It is not screen");

    activeScreen = screen;
}

void PMaster::main()
{
    //v tomhle vlákně bude periodicky pročitat všechny eventy a zpracovat je
    //až to jednou projde zavolá port->suspend
    //probrání si musi pořešit porting třeba přes nějaky přerušeni od tlačitek nebo od touche že má novy data
    //ještě je potřeba promyslet probrání při změně něčeho ne od usera ale přimo programem(hodiny..)
    printScreen();
}

}
