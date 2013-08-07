#include "ptouchevent.h"
#include "ptypes.h"

namespace piris
{

PTouchEvent::PTouchEvent():
    event(NONE),
    x(0),
    y(0),
    xRelative(0),
    yRelative(0),
    dragLocked(0)
{
}

}
