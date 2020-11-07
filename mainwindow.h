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
    int x = 0; // позиция мыши по Х
    int y = 0; // позиция мыши по У
    int R = 50; // радиус круга
    bool Alloc = false; // выделен круг или нет
    QPainter *p = nullptr; // отрисовка круга
public:
    CCircle () = default;
    CCircle (CCircle *x){
        this->x = x->x; // получение координат мыши по х
        this->y = x->y; // получение координат мыши по у
        this->R = x->R; // получение радиуеса
        this->p = x->p; // получение объекта
    }
    CCircle(int x, int y){
        this->x = x; // исключение отклонений по Х
        this->y = y; // исключение отклонений по У
    }
    virtual int getx(){ // возврат значения по Х
        return this->x;
    }
    virtual int gety(){ // возврат значения по У
        return this->y;
    }
    virtual int getR(){ // возврат значения по R
        return this->R;
    }
    virtual bool getAlloc(){ // получение статуса объекта (закрашен ли?)
        return this->Alloc;
    };
    virtual void setAlloc(bool f){ // установка статуса объекта
        this->Alloc = f;
    }
    virtual void draw(QWidget *parent){ // метод отрисовки
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
