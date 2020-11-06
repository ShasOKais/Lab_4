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

void MainWindow::ClearAllocs() // Функция развыделения кругов
{
    for(int i = 0; i < stor.size(); i++){
        stor[i]->setAlloc(false); // Развыделить все круги в массиве
    }
}

void MainWindow::ReverseAlloc(int pos) // Функция инверсии выделения круга(ов)
{
    stor[pos]->getAlloc() == false ? stor[pos]->setAlloc(true) : stor[pos]->setAlloc(false);
}

int MainWindow::FindStrike(QMouseEvent *e) // Функция проверки попадания по кругу и какому кругу
{
    int x = e->x(); // позиция мыши по Х
    int y = e->y(); // позиция мыши по У
    for(int i = stor.size() - 1; i >= 0; i--){
        int X = stor[i]->getx();
        int Y = stor[i]->gety();
        int R = stor[i]->getR();
        int len  = sqrt((X - x)*(X - x) + (Y - y)*(Y - y)); // Формула вычисления попадания
        if(len <= R) { // если попал
            return i; // вернуть позицию круга в хранилище
        }
    }
    return -1; // иначе не попал ни по одному
}

void MainWindow::addNewCircle(QMouseEvent *e)
{
    ClearAllocs(); // развыделить все круги
    stor.push_back(new CCircle(e->x(), e->y())); // вставить новый круг в конец массива
    stor.back()->setAlloc(true); // выделить его
}

void MainWindow::DeleteAllocs() // Функция удаления выделенных кругов
{
    for(int i = 0; i < stor.size(); i++){
        if(stor[i]->getAlloc()){
            stor.Delete(i);
            i--;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) // Функция при отжатии клавиши Ctrl
{
    if(e->key() == Qt::Key_Control) {
        is_CTRL_Hold = false; // Клавиша больше не удерживается
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e) // При нажатии кнопки ЛКМ
{
    if(e->button() == Qt::LeftButton){
        int posStriked = FindStrike(e); // задаем переменную попадания чтобы не обращаться к ней вновь
        if(is_CTRL_Hold){ // если CTRL зажат
            if(posStriked != -1){ // если синий инвертируем в белый, иначе наооборот
                ReverseAlloc(posStriked);
            }
        } else {
            if(posStriked != -1){ // иначе если попали без зажатого CTRL
                ClearAllocs(); // убираем выделение с остальных кружков
                ReverseAlloc(posStriked); // инвертируем цвет в выделенный, т.е. белый в синий
            } else {
                addNewCircle(e); // если же не попали и не зажали, то создаем новый круг и выделяем его сразу же
            }
        }
    }
    repaint(); // отрисовываем по новой
}

void MainWindow::keyPressEvent(QKeyEvent *d) // Функция регистрации нажатии "нужных" клавиш
{
    if(d->key() == Qt::Key_Delete){
        DeleteAllocs();
    }
    if(d->key() == Qt::Key_Control){
        is_CTRL_Hold = true;
    }
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *){ // отрисовка при обновлении формы
    for(int i(0); i < stor.size(); i++){
        stor[i]->draw(this);
    }
}
