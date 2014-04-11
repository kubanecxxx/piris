#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "porting.h"
#include "pkeyevent.h"
#include <QTimer>
#include "pwidget.h"
#include "pmaster.h"
#include "pscreen.h"
#include "qdebugprint.h"
#include "pbutton.h"
#include "pfont.h"
#include <QDebug>
#include "plabel.h"

extern piris::PMaster * guiInit(piris::PPortingAbstract * port, int & siz);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    qDebugPrint::edit = ui->textBrowser;



    ui->display->setFocus();

    QTimer * timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(50);

    connect(ui->display,SIGNAL(mouseCoord(QPoint)),this,SLOT(mousePos(QPoint)));

    piris::PPortingAbstract * port;
    port = new porting(ui->display);

    //ui->display->setMinimumSize(200,300);
    ui->display->setMinimumSize(128,160);

    /*
     **********************************************
     */

    int size;
    mast = guiInit(port,size);


    ui->spinMemory->setValue(size);

    //temp = new piris::PWidget(coje);
    //temp->setX(50);

    asm("nop");

    mast->printScreen();
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
