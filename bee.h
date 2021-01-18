#ifndef BEE_H
#define BEE_H
#include "base.h"


class bee : public base
{
private:
    float r;
    float time;
public:
    bee();
    bee(float rad, float ra, std::array<float,2> p, float vx);
    void Advance(float t);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);

};

#endif // BEE_H
