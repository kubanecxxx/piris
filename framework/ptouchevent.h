#ifndef PTOUCHEVENT_H
#define PTOUCHEVENT_H

#include "ptypes.h"

namespace piris
{

class PWidget;
class PTouchEvent
{
public:
    PTouchEvent();

public:
    inline PWidget * locked() const {return dragLocked;}
    inline void lock(PWidget * widget) {dragLocked = widget;}
    inline void unlock() {dragLocked = 0;}


    touchEvt_t event;
    pixel_t x;
    pixel_t y;

    void operator=(const PTouchEvent & other)
    {
        x = other.x;
        y = other.y;
        event = other.event;
    }

    bool operator==(const PTouchEvent & other)
    {
        return (x == other.x && y == other.y && event == other.event);
    }


private:
    PWidget * dragLocked;
};

}
#endif // PTOUCHEVENT_H
