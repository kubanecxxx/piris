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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebugPrint::edit = ui->textBrowser;

    piris::PPortingAbstract * port;
    port = new porting(ui->display);

    ui->display->setFocus();

    QTimer * timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(100);

    connect(ui->display,SIGNAL(mouseCoord(QPoint)),this,SLOT(mousePos(QPoint)));

    ui->display->setMinimumSize(200,300);

    mast = new piris::PMaster(port);

    piris::PScreen * wid;
    wid = new piris::PScreen(mast);
    wid->name = "screen1";

    piris::PWidget * temp = new piris::PWidget();
    temp->setColor(piris::GREEN);
    temp->setX(40);
    temp->setY(40);
    temp->setWidth(100);
    temp->setHeight(100);
    temp->name = ("widget 1");
    wid->addChild(temp);

    temp = new piris::PWidget();
    temp->setColor(piris::BLACK);
    temp->setX(80);
    temp->setY(80);
    temp->setWidth(100);
    temp->setHeight(100);
    temp->name = ("widget 2");
    wid->addChild(temp);


    temp = new piris::PButton();
    temp->setColor(piris::WHITE);
    temp->setX(20);
    temp->setY(200);
    temp->setWidth(100);
    temp->setHeight(50);
    temp->name = ("widget 3");
    temp->setText("curakasldfj");
    temp->setTextColor(piris::BLACK);
    wid->addChild(temp);



    temp->setFocus();
    wid->makeActive();

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
