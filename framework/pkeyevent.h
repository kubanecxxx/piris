#ifndef PKEYEVENT_H
#define PKEYEVENT_H

#include "ptypes.h"

namespace piris
{


/**
 * @brief The PKeyEvent class
 *
 *
 */
class PKeyEvent
{
public:
    PKeyEvent();

public:
    keyEvt_t event;
    key_t key;
};

}
#endif // PKEYEVENT_H
