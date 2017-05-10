#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QWheelEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    lw = new LabiryntView(8, 6, ui->graphicsView);
    connect(ui->setStart, SIGNAL(clicked(bool)), lw, SLOT(setStart()));
    connect(ui->setEnd, SIGNAL(clicked(bool)), lw, SLOT(setEnd()));
    connect(lw, SIGNAL(success()), this, SLOT(uncheck()));
    connect(ui->zoomIn, SIGNAL(clicked(bool)), this, SLOT(zoomIn()));
    connect(ui->zoomOut, SIGNAL(clicked(bool)), this, SLOT(zoomOut()));
}

void MainWindow::zoomIn(){
    ui->graphicsView->scale(1.1, 1.1);
}

void MainWindow::zoomOut(){
    ui->graphicsView->scale(0.9, 0.9);
}

void MainWindow::printMaze(){

}

void MainWindow::uncheck(){
    ui->setStart->setAutoExclusive(false);
    ui->setStart->setChecked(false);
    ui->setStart->setAutoExclusive(true);
    ui->setEnd->setAutoExclusive(false);
    ui->setEnd->setChecked(false);
    ui->setEnd->setAutoExclusive(true);
}


MainWindow::~MainWindow(){
    delete ui;
}
