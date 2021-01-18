#ifndef FROG_H
#define FROG_H
#include "base.h"
#include "tong.h"


class frog :public base
{
private:
    int life;
public:
    frog();
    frog(float ra, std::array<float,2> p, float vx);
    tong *lengua;
    void Advance(float t);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);
    void setlife(int vida);
    void gethit(int golpe);
};

#endif // FROG_H
