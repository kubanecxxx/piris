#ifndef QDISPLAY_H
#define QDISPLAY_H

#include <QWidget>
#include <QFrame>
#include <QPicture>
#include <QPainter>
#include <QRgb>

namespace Ui {
class QDisplay;
}

class QDisplay : public QFrame
{
    Q_OBJECT
    
public:
    explicit QDisplay(QWidget *parent = 0);
    ~QDisplay();
    
private:
    Ui::QDisplay *ui;

    void keyPressEvent(QKeyEvent * key);
    void keyReleaseEvent(QKeyEvent * key);
    void mousePressEvent(QMouseEvent * mouse);
    void mouseReleaseEvent(QMouseEvent * mouse);
    void mouseMoveEvent(QMouseEvent * mouse);
    void paintEvent(QPaintEvent *);

    typedef enum
    {
        NONE, PIXEL
    } action_t;

    QImage * image;
    QPainter p;

signals:
    void skeyPressEvent(QKeyEvent *key);
    void skeyReleaseEvent(QKeyEvent *key);
    void smouseMoveEvent(QMouseEvent *mouse);
    void smousePressEvent(QMouseEvent *mouse);
    void smouseReleaseEvent(QMouseEvent *mouse);

public:
    void putPixel(int x , int y , QColor color);
    void putText(int x, int y, const char * data, QColor col, int size);
    void putRect(int x1, int x2, int y1, int y2, QColor color);
};

#endif // QDISPLAY_H
