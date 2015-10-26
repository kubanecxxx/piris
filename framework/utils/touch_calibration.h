#ifndef TOUCH_CALIBRATION_H
#define TOUCH_CALIBRATION_H

#ifdef PIRIS_USE_CALIBRATOR

#include <stdint.h>

namespace piris
{
class PPortingAbstract;
class PTouchEvent;


class touchCalibration
{
public:
    typedef struct
    {
        int32_t kx;     //* 100
        int32_t ky;     //* 100
        int32_t qx;     //* 1
        int32_t qy;     //* 1
    } corrections_t;

    touchCalibration(piris::PPortingAbstract & port);
    void loop();
    bool finished(corrections_t * corrections);

    static void rawToPixels(piris::PTouchEvent * evt, const corrections_t * cor);

private:
    piris::PPortingAbstract & port;
    uint8_t machine;
    uint8_t superMachine ;
    bool fin;

    uint16_t rawx[3];
    uint16_t rawy[3];
    corrections_t cor;
};

}

#endif
#endif // TOUCH_CALIBRATION_H

