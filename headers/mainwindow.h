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
    int m_delay;
    bool m_canGo = true;
    QString m_fileName;

public slots:
    void zoomIn();
    void zoomOut();
    void uncheck();
    void tabClicked(int index);
    bool step();
    void solve();
    void resetSearch();
    void algorithmSelected(int index);
    void speedSelected(int index);
    void newLabirynth();
    void save();
    void load();
};

#endif // MAINWINDOW_H
