#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace piris
{
    class PPortingAbstract;
    class PWidget;
    class PMaster;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;


    piris::PMaster * mast;

private slots:
    void timeout(void);
    void mousePos(const QPoint & pos);
};

#endif // MAINWINDOW_H
