#ifndef MATY_H
#define MATY_H
#include "base.h"
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QGraphicsItem>


class maty : public base
{
private:
    float vx=5;
    float vy=20;
public:
    maty();
    maty(float d ,float h,std::array<float,2> p,float ay);
    void up();
    void down();
    void right();
    void left();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);
    float ry;
    float rx;
    int life;
    explicit maty( QObject *parent = nullptr);
    QPixmap *pixmap;
    void sprintstate();
    int columnas,filas;
    void Advance(float t);



};

#endif // MATY_H
