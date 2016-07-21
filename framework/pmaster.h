#ifndef PMASTER_H
#define PMASTER_H

#ifdef PIRIS_USE_CALIBRATOR
#include "utils/touch_calibration.h"
#endif

namespace piris
{

class PPortingAbstract;
class PScreen;
class PKeyEvent;
class PTouchEvent;

class PMaster
{
public:
    PMaster(PPortingAbstract * port);
    PMaster(PKeyEvent * k, PTouchEvent * t);
    inline bool touchEventHappened() const {return touchHappen;}
    inline bool keyEventHappened() const {return keyHappen;}

private:
    PPortingAbstract * hw;
    PScreen * activeScreen;
    PMaster(const PMaster &);

    PKeyEvent * key;
    PTouchEvent * touch;

    bool touchHappen;
    bool keyHappen;

public:
    void setActiveScreen(PScreen * screen);
    void printScreen();
    void main();
#ifdef PIRIS_USE_CALIBRATOR
    void main(touchCalibration * calibrator, const touchCalibration::corrections_t * corrections, bool calibrate);
#endif

    inline void setHW(PPortingAbstract * port) {hw = port;}

    PScreen * getActiveScreen() const {return activeScreen;}

};

}

#endif // PMASTER_H
