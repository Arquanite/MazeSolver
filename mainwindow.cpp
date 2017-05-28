#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include "autisticsearch.h"
#include "dfsearch.h"
#include "bfsearch.h"
#include "randomfirst.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    qsrand(time(NULL));
    lw = new LabiryntView(8, 5, ui->graphicsView);
    connect(ui->buttonSetStart, SIGNAL(clicked(bool)), lw, SLOT(setStart()));
    connect(ui->buttonSetEnd, SIGNAL(clicked(bool)), lw, SLOT(setEnd()));
    connect(lw, SIGNAL(success()), this, SLOT(uncheck()));
    connect(ui->buttonZoomIn, SIGNAL(clicked(bool)), this, SLOT(zoomIn()));
    connect(ui->buttonZoomOut, SIGNAL(clicked(bool)), this, SLOT(zoomOut()));
    connect(ui->buttonZoomIn_2, SIGNAL(clicked(bool)), this, SLOT(zoomIn()));
    connect(ui->buttonZoomOut_2, SIGNAL(clicked(bool)), this, SLOT(zoomOut()));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabClicked(int)));

    connect(ui->buttonStep, &QPushButton::clicked, [=](){ ui->buttonSolve->setEnabled(true); m_canGo = false; step(); });
    connect(ui->buttonSolve, &QPushButton::clicked, [=](){ ui->buttonSolve->setEnabled(false); m_canGo = true; solve(); });
    connect(ui->selectAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(algorithmSelected(int)));
    connect(ui->selectSpeed, SIGNAL(currentIndexChanged(int)), this, SLOT(speedSelected(int)));
    connect(ui->buttonRandom, SIGNAL(clicked(bool)), lw, SLOT(toggleRandomEdge()));
    connect(ui->buttonReset, SIGNAL(clicked(bool)), this, SLOT(resetSearch()));
    algorithmSelected(0);
    speedSelected(2);
    tabClicked(0);
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
    if(index == 0){
        lw->setEditable(true);
        m_canGo = false;
    }
    else {
        lw->setEditable(false);
        if(lw->start() == -1 || lw->end() == -1){
            QMessageBox::warning(this, "STAPH!!1", "U CANT SOLVE WHEN U HAVE NOT START AND END NOT TOO!!11");
            QTimer::singleShot(10, [=](){ui->tabWidget->setCurrentIndex(0);});
            lw->setEditable(true);
            return;
        }
        resetSearch();
    }
    uncheck();
}

bool MainWindow::step(){
    bool next = false;
    AbstractAlgorithm::AlgorithmState result = m_algorithm->step();
    lw->setPath(m_algorithm->path());
    lw->setVisitedList(m_algorithm->visited());
    switch (result){
    case AbstractAlgorithm::Finish:
        QMessageBox::information(this, "Success", "Found a way to end!");
        ui->buttonSolve->setEnabled(true);
        break;
    case AbstractAlgorithm::Working:
        next = true;
        break;
    case AbstractAlgorithm::Lost:
        QMessageBox::information(this, "No way to end!", "There is no way to end!");
        ui->buttonSolve->setEnabled(true);
        break;
    default:
        QMessageBox::warning(this, "Wystąpił błąd!", "Algorytm nie działa tak jak powinien, skontaktuj się z twórcą oprogramowania."); //do poprawy
    }
    return next;
}

void MainWindow::solve(){
    if(m_canGo && step()) QTimer::singleShot(m_delay, [=](){ solve(); });
    m_canGo = true;
}

void MainWindow::resetSearch(){
    m_canGo = false;
    m_algorithm->reset();
    m_algorithm->setGraph(lw->graph());
    m_algorithm->setStart(lw->start());
    m_algorithm->setEnd(lw->end());
    lw->setEditable(false);
    ui->buttonSolve->setEnabled(true);
}

void MainWindow::algorithmSelected(int index){
    AbstractAlgorithm *alg = nullptr;
    switch(index){
    case 0: // Depth first
        alg = new DFSearch();
        break;
    case 1: // Breadth first
        alg = new BFSearch();
        break;
    case 2: // Autistic first
        alg = new AutisticSearch();
        break;
    case 3: // Random first
        alg = new RandomFirst();
        break;
    default:
        QMessageBox::warning(this, "ACHTUNG!", "DER IZ NO SUCH ALGORITHM!!11");
        break;
    }
    if(alg != nullptr){
        delete m_algorithm;
        m_algorithm = alg;
    }
    resetSearch();
}

void MainWindow::speedSelected(int index){
    switch (index) {
    case 0:
        m_delay = 10;
        break;
    case 1:
        m_delay = 100;
        break;
    case 2:
        m_delay = 500;
        break;
    case 3:
        m_delay = 1000;
        break;
    }
}

MainWindow::~MainWindow(){
    delete ui;
}
