#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QDebug>
#include "autisticsearch.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    lw = new LabiryntView(8, 5, ui->graphicsView);
    connect(ui->buttonSetStart, SIGNAL(clicked(bool)), lw, SLOT(setStart()));
    connect(ui->buttonSetEnd, SIGNAL(clicked(bool)), lw, SLOT(setEnd()));
    connect(lw, SIGNAL(success()), this, SLOT(uncheck()));
    connect(ui->buttonZoomIn, SIGNAL(clicked(bool)), this, SLOT(zoomIn()));
    connect(ui->buttonZoomOut, SIGNAL(clicked(bool)), this, SLOT(zoomOut()));
    connect(ui->buttonZoomIn_2, SIGNAL(clicked(bool)), this, SLOT(zoomIn()));
    connect(ui->buttonZoomOut_2, SIGNAL(clicked(bool)), this, SLOT(zoomOut()));

    connect(ui->tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(tabClicked(int)));

    connect(ui->buttonStep, SIGNAL(clicked(bool)), this, SLOT(step()));
    connect(ui->selectAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(algorithmSelected()));
    algorithmSelected();
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
    ui->buttonSetStart->setAutoExclusive(false);
    ui->buttonSetStart->setChecked(false);
    ui->buttonSetStart->setAutoExclusive(true);
    ui->buttonSetEnd->setAutoExclusive(false);
    ui->buttonSetEnd->setChecked(false);
    ui->buttonSetEnd->setAutoExclusive(true);
}

void MainWindow::tabClicked(int index){
    if(index == 0) lw->setEditable(true);
    else {
        lw->setEditable(false);
        if(lw->start() == -1 || lw->end() == -1){
            QMessageBox::warning(this, "STAPH!!1", "U CANT SOLVE WHEN U HAVE NOT START AND END NOT TOO!!11");
            QTimer::singleShot(10, [=](){ui->tabWidget->setCurrentIndex(0);});
        }
        m_algorithm->reset();
        m_algorithm->setGraph(lw->graph());
        m_algorithm->setStart(lw->start());
        m_algorithm->setEnd(lw->end());
    }
    uncheck();
}

void MainWindow::step(){
    qDebug()<<"Step";
    if(m_algorithm->step()) QMessageBox::information(this, "Xdd", "Udao siem");
    lw->setPath(m_algorithm->path());
}

void MainWindow::algorithmSelected(){
    qDebug()<<"select";
    delete m_algorithm;
    m_algorithm = new AutisticSearch();
    m_algorithm->setStart(lw->start());
    m_algorithm->setEnd(lw->end());
    lw->setNormal();
}

MainWindow::~MainWindow(){
    delete ui;
}
