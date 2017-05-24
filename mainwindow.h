#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "labiryntview.h"
#include "abstractalgorithm.h"

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
    AbstractAlgorithm *m_algorithm = nullptr;

public slots:
    void zoomIn();
    void zoomOut();
    void printMaze();
    void uncheck();
    void tabClicked(int index);
    void step();
    void algorithmSelected(int index);
};

#endif // MAINWINDOW_H
