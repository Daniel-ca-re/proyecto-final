#ifndef BALA_H
#define BALA_H
#include "base.h"


class bala : public base
{
public:
    bala();
    bala( float ra, std::array<float,2> p, std::array<float,2> v);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);
};

#endif // BALA_H
