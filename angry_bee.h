#ifndef ANGRY_BEE_H
#define ANGRY_BEE_H
#include "base.h"


class angry_bee: public base
{
private:
    float v;
public:
    angry_bee();
    angry_bee( float ra, std::array<float,2> p, float v);
    void Advance(float t,std::array<float,2> p);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);

};

#endif // ANGRY_BEE_H
