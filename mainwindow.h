#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "labiryntview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LabiryntView *lw;

public slots:
    void zoomIn();
    void zoomOut();
    void printMaze();
    void uncheck();
};

#endif // MAINWINDOW_H
