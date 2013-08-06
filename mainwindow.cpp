#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "porting.h"
#include "pkeyevent.h"
#include <QTimer>
#include "pwidget.h"
#include "pmaster.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    piris::PPortingAbstract * port;
    port = new porting(ui->display);

    ui->display->setFocus();

    QTimer * timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(50);

    connect(ui->display,SIGNAL(mouseCoord(QPoint)),this,SLOT(mousePos(QPoint)));

    ui->display->setMinimumSize(200,300);

    mast = new piris::PMaster(port);

    piris::PWidget * wid;
    wid = new piris::PWidget(mast);
    wid->name = "screen1";

    piris::PWidget * temp = new piris::PWidget(wid);
    temp->setColor(piris::GREEN);
    temp->setX(40);
    temp->setY(40);
    temp->setWidth(100);
    temp->setHeight(100);
    temp->name = "widget1";

    mast->setActiveScreen(wid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeout()
{
    mast->main();
}


void MainWindow::mousePos(const QPoint &pos)
{
    ui->spinX->setValue(pos.x());
    ui->spinY->setValue(pos.y());
}
