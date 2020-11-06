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
        p->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap)); // черная ручка
        if(Alloc == false){
            p->setBrush(QBrush(Qt::white, Qt::SolidPattern)); // круг с черной окантовкой и внутри белый

        } else {
            p->setBrush(QBrush(Qt::blue, Qt::SolidPattern)); // круг с черной окантовкой и синий
        }
        p->drawEllipse(x - R, y - R, 2 * R, 2 * R); // нарисовать круг
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
    void mousePressEvent(QMouseEvent *e); // по нажатию кнопки мыши срабатывает триггер
    void keyPressEvent(QKeyEvent *d); // при нажатии клавиши срабатывает триггер
    int FindStrike(QMouseEvent *e); // при попадании в круг возвращает позицию круга в хранилище
    void addNewCircle(QMouseEvent *e); // функция добавления круга на форму
    void DeleteAllocs(); // удаляет выделенные круги по нажатию клавиши
    void ClearAllocs(); // очищает выделенные круги, преобразуя их в невыделенные
    void ReverseAlloc(int pos); // принимает позицию круга и инвертирует выделение
    void keyReleaseEvent(QKeyEvent *e); // при отжатии клавиши срабатывает триггер
};

#endif // MAINWINDOW_H
