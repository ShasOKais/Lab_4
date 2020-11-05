#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MyVector.h"

#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// начало
class CShape{
public:
    virtual void draw(QWidget *parent){};
    virtual ~CShape(){};
    virtual int getx(){};
    virtual int gety(){};
    virtual int getR(){};
    virtual bool getAlloc(){};
    virtual void setAlloc(bool f){};
};

class CCircle: public CShape{ // Создание круга
private:
    int x = 0;
    int y = 0;
    int R = 50;
    bool Alloc = false;
    QPainter *p = nullptr;
public:
    CCircle () = default;
    CCircle (CCircle *x){
        this->x = x->x;
        this->y = x->y;
        this->R = x->R;
        this->p = x->p;
    }
    CCircle(int x, int y){
        this->x = x;
        this->y = y;
    }
    virtual int getx(){
        return this->x;
    }
    virtual int gety(){
        return this->y;
    }
    virtual int getR(){
        return this->R;
    }
    virtual bool getAlloc(){
        return this->Alloc;
    };
    virtual void setAlloc(bool f){
        this->Alloc = f;
    }
    virtual void draw(QWidget *parent){
        p = new QPainter(parent);
        p->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        if(Alloc == false){
            p->setBrush(QBrush(Qt::white, Qt::SolidPattern));

        } else {
            p->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        }
        p->drawEllipse(x - R, y - R, 2 * R, 2 * R);
    }
    virtual ~CCircle(){};
};
// конец

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    SimpleVector<CShape*> stor; // Хранилище кругов под глазами
    bool is_CTRL_Hold = false;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
protected:
    void mousePressEvent(QMouseEvent *e); // по нажатию мыши чето происходит
    void keyPressEvent(QKeyEvent *d);
    int FindStrike(QMouseEvent *e);
    void addNewCircle(QMouseEvent *e);
    void DeleteAllocs();
    void ClearAllocs();
    void ReverseAlloc(int pos);
    void keyReleaseEvent(QKeyEvent *e);
};

#endif // MAINWINDOW_H
