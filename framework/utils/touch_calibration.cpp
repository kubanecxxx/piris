
#ifdef PIRIS_USE_CALIBRATOR

#include "passert.h"
#include "pportingabstract.h"
#include "ptouchevent.h"
#include "touch_calibration.h"
#include "pfont.h"

namespace piris
{



touchCalibration::touchCalibration(piris::PPortingAbstract &p):
    port(p)
{
    machine = 0;
    superMachine = 0;
    fin = false;
}

void touchCalibration::loop()
{
    piris::PTouchEvent evt;
    //state machine
    //draw 3 crosses
    //read 3 values
    //compute corrections

    if (machine == 0)
    {
        port.fill(piris::GREEN);
        port.putText("Calibration", 50,50,piris::PFont::sans16, piris::BLACK);
        uint16_t x,y;
        if (superMachine == 0)
        {
            x = 20;
            y = 20;
        }
        else if (superMachine == 1)
        {
            x = port.width() - 20;
            y = 20;
        }
        else if (superMachine == 2)
        {
            x = 20;
            y = port.height() - 20;
        }

        port.putLine(x,x,y-10, y+10,piris::BLUE);
        port.putLine(x-10,x+10,y,y,piris::BLUE);
        machine++;
    }
    else if (machine == 1)
    {
        //wait for press
        if (port.readTouchEvent(&evt))
        {
            if (evt.event == piris::PRESS)
            {
                rawx[superMachine] = evt.x;
                rawy[superMachine] = evt.y;
                machine++;
            }
        }
    }
    else if (machine == 2)
    {
        if (port.readTouchEvent(&evt))
        {
            if (evt.event == piris::RELEASE)
            {
                machine = 0;
                qlog(QString("calibrator clicked %1").arg(superMachine));
                superMachine++;
            }
        }
    }

    if (superMachine == 3)
    {
        machine = 0xff;
        port.fill(piris::GREEN);
        port.putText("Now test!", 50,50,piris::PFont::sans16, piris::BLACK);
        //finish

        //compute coeficients
        cor.kx = ((port.width() - 40) * 100 )/ (rawx[1] - rawx[0]);
        cor.qx = ((20 * 100) - rawx[0] * cor.kx) / 100;

        cor.ky = ((port.height() - 40) * 100) / (rawy[2] - rawy[0]);
        cor.qy = ((20 * 100) - rawy[0] * cor.ky) / 100;

        fin = true;
        superMachine++;
    }
    else if (superMachine == 4)
    {
        if (port.readTouchEvent(&evt))
        {
            if (evt.event == piris::PRESS)
            {
                rawToPixels(&evt, &cor);
                port.putPixel(evt.x,evt.y, piris::BLACK);
            }
        }
    }
}

bool touchCalibration::finished(corrections_t * cor)
{
    if (fin)
        memcpy(cor,&(this->cor), sizeof(corrections_t));

    return fin;
}

void touchCalibration::rawToPixels(piris::PTouchEvent *evt, const corrections_t * cor)
{
    evt->x = ((evt->x * cor->kx) / 100) + cor->qx;
    evt->y = ((evt->y * cor->ky) / 100) + cor->qy;
}

}

#endif
