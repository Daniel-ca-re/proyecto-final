#ifndef FROG_H
#define FROG_H
#include "base.h"
#include "tong.h"
#include "platform.h"


class frog :public base
{
private:

public:
    frog();
    frog(float ra, std::array<float,2> p, float vx);
    tong *lengua;
    platform *lengua2;
    void Advance(float t);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);
    void setlife(int vida);
    void gethit(int golpe);
    int life;
    QPixmap *pixmap;
    void sprintstate();
    int columnas,filas;
};

#endif // FROG_H
