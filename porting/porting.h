#ifndef PORTING_H
#define PORTING_H

#include "pportingabstract.h"
#include <QObject>
#include <QColor>
#include <QRgb>

class QDisplay;
class QMouseEvent;
class QKeyEvent;

namespace piris
{
    class PKeyEvent;
    class PTouchEvent;

}

class porting: public QObject, public piris::PPortingAbstract
{
    Q_OBJECT
public:
    porting(QDisplay * dsp);

private:
    bool readKeyEvent(piris::PKeyEvent *evt);
    bool readTouchEvent(piris::PTouchEvent *evt);

    void putPixel(piris::pixel_t x, piris::pixel_t y, piris::PColor color);
    void putText(const char *text, piris::pixel_t x, piris::pixel_t y,const piris::PFont & font,piris::PColor color);
    void putRectangle(piris::pixel_t x1, piris::pixel_t x2, piris::pixel_t y1, piris::pixel_t y2, piris::PColor color);
    void fill(piris::PColor color);
    void putLine(piris::pixel_t x1, piris::pixel_t x2, piris::pixel_t y1, piris::pixel_t y2, piris::PColor color);

    piris::pixel_t height() const ;
    piris::pixel_t width() const;

private:
    QDisplay * disp;

    piris::PKeyEvent * key;
    piris::PTouchEvent * touch;

    bool full;
    bool touchfull;
    int key2key(uint16_t);

private slots:
    void keyPressEvent(QKeyEvent *key);
    void keyReleaseEvent(QKeyEvent *key);
    void mouseMoveEvent(QMouseEvent *mouse);
    void mousePressEvent(QMouseEvent *mouse);
    void mouseReleaseEvent(QMouseEvent *mouse);

};

#endif // PORTING_H
