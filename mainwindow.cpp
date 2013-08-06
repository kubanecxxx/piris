#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "porting.h"
#include "pkeyevent.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   port = new porting(ui->display);

    ui->display->setFocus();

    QTimer * timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(50);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeout()
{
    piris::PKeyEvent evt;

    static int i = 10;
    if (port->readKeyEvent(&evt))
    {
        port->putPixel(i++,100,piris::PColor(piris::GREEN));
        port->putText("moje",10,10 * i,8,piris::PColor(piris::RED));
        port->putRectangle(0,10,0,30,piris::PColor(piris::BLUE));

    }


}
