#include "ptouchevent.h"
#include "ptypes.h"

namespace piris
{

PTouchEvent::PTouchEvent():
    event(NONE),
    x(0),
    y(0),
    dragLocked(0)
{
}

}
