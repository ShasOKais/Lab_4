#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QDebug>
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

void MainWindow::ClearAllocs()
{
    for(int i = 0; i < stor.size(); i++){
        stor[i]->setAlloc(false);
    }
}

void MainWindow::ReverseAlloc(int pos)
{
    stor[pos]->getAlloc() == false ? stor[pos]->setAlloc(true) : stor[pos]->setAlloc(false);
}

int MainWindow::FindStrike(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    for(int i = stor.size() - 1; i >= 0; i--){
        int X = stor[i]->getx();
        int Y = stor[i]->gety();
        int R = stor[i]->getR();
        int len  = sqrt((X - x)*(X - x) + (Y - y)*(Y - y));
        if(len <= R) {
            return i;
        }
    }
    return -1;
}

void MainWindow::addNewCircle(QMouseEvent *e)
{
    ClearAllocs();
    stor.push_back(new CCircle(e->x(), e->y()));
    stor.back()->setAlloc(true);
}

void MainWindow::DeleteAllocs()
{
    for(int i = 0; i < stor.size(); i++){
        if(stor[i]->getAlloc()){
            stor.Delete(i);
            i--;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control) {
        is_CTRL_Hold = false;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        int posStriked = FindStrike(e);
        if(is_CTRL_Hold){
            if(posStriked != -1){
                ReverseAlloc(posStriked);
            }
        } else {
            if(posStriked != -1){
                ClearAllocs();
                ReverseAlloc(posStriked);
            } else {
                addNewCircle(e);
            }
        }
    }
    repaint();
}

void MainWindow::keyPressEvent(QKeyEvent *d)
{
    if(d->key() == Qt::Key_Delete){
        DeleteAllocs();
    }
    if(d->key() == Qt::Key_Control){
        is_CTRL_Hold = true;
    }
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *){
    for(int i(0); i < stor.size(); i++){
        stor[i]->draw(this);
    }
}
