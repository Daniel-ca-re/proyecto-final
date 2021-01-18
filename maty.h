#ifndef MATY_H
#define MATY_H
#include "base.h"


class maty : public base
{
private:
    int life;
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


};

#endif // MATY_H
