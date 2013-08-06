#include "qdisplay.h"
#include "ui_qdisplay.h"
#include <QPaintEvent>
#include <QPainter>

QDisplay::QDisplay(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QDisplay)

{
    ui->setupUi(this);
    setAutoFillBackground(false);

    image = new QImage(width(),height(),QImage::Format_RGB32);
    image->fill(QColor(Qt::black).rgb());
}

QDisplay::~QDisplay()
{
    delete ui;
}


void QDisplay::keyPressEvent(QKeyEvent *key)
{
    emit skeyPressEvent(key);
}

void QDisplay::keyReleaseEvent(QKeyEvent *key)
{
    emit skeyReleaseEvent(key);
}

void QDisplay::mouseMoveEvent(QMouseEvent *mouse)
{
    QFrame::mouseMoveEvent(mouse);
    emit smouseMoveEvent(mouse);
}

void QDisplay::mousePressEvent(QMouseEvent *mouse)
{
     QFrame::mousePressEvent(mouse);
     setFocus();
    emit smousePressEvent(mouse);
}

void QDisplay::mouseReleaseEvent(QMouseEvent *mouse)
{
    QFrame::mouseReleaseEvent(mouse);
    emit smouseReleaseEvent(mouse);
}

void QDisplay::paintEvent(QPaintEvent *evt)
{
    QFrame::paintEvent(evt);

    QPainter p;
    p.begin(this);
    p.drawImage(0,0,*image,0,0,width(),height());
}

void QDisplay::putPixel(int x, int y, QColor color)
{
    image->setPixel(x,y,color.rgb());
    repaint();
}

void QDisplay::putText(int x, int y, const char *data, QColor col, int size)
{
    QPainter p;
    p.begin(image);
    p.setPen(col);
    QFont font;
    font.setFamily("terminus");
    font.setPixelSize(size);
    p.setFont(font);
    p.drawText(x,y,QString(data));

    repaint();
}

void QDisplay::putRect(int x1, int x2, int y1, int y2, QColor color)
{
    QPainter p;
    p.begin(image);
    p.setPen(color);
    QFont font;
    p.fillRect(x1,y1,x2-x1,y2-y1,color);


    repaint();
}
