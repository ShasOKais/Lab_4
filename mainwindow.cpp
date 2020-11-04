#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    bool f(0);
    for(int i(stor.size() - 1); i >= 0; i--){
        int X = stor[i]->getx();
        int Y = stor[i]->gety();
        int R = stor[i]->getR();
        //int len  = sqrt((X-x)*(X-x) + (Y-y)*(Y-y));
    }
    if(!f)stor.push_back(new CCircle(e->x(), e->y()));
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *){
    for( int i(0); i<stor.size(); i++){
            stor[i]->draw(this);
    }
}
