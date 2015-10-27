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
#include "utils/touch_calibration.h"

extern piris::PMaster * guiInit(piris::PPortingAbstract * port, int & siz);
extern piris::PMaster * mirekGuiInit(piris::PPortingAbstract * port, int & siz);
extern piris::PMaster * lichtmustrGuiInit(piris::PPortingAbstract * port, int & size);
piris::touchCalibration * cal ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    qDebugPrint::edit = ui->textBrowser;

    QPalette palette;
    palette.setBrush(QPalette::Base, Qt::NoBrush);
    setPalette(palette);
    // Required to display wallpaper
    //setAttribute(Qt::WA_TranslucentBackground);
    // no border at all finally

    //setFrameShape(QFrame::NoFrame);
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_NoBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setAttribute(Qt::WA_OpaquePaintEvent, true);
    //setAttribute(Qt::WA_PaintOnScreen);
    //setAutoFillBackground(true);
    //setWindowOpacity(1);

    ui->display->setFocus();

    QTimer * timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(50);

    connect(ui->display,SIGNAL(mouseCoord(QPoint)),this,SLOT(mousePos(QPoint)));

    piris::PPortingAbstract * port;
    port = new porting(ui->display);

    ui->display->setMinimumSize(120,160);
    //ui->display->setMinimumSize(320,240);

    /*
     **********************************************
     */

    int size;
    mast = guiInit(port,size);
    //mast = mirekGuiInit(port,size);
    //mast = lichtmustrGuiInit(port,size);

    //ui->spinMemory->setValue(size);

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
    //cal->loop();
}


void MainWindow::mousePos(const QPoint &pos)
{
    ui->spinX->setValue(pos.x());
    ui->spinY->setValue(pos.y());
}
