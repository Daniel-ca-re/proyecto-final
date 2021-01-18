#ifndef FRICTION_LAYER_H
#define FRICTION_LAYER_H
#include "base.h"


class friction_layer : public base
{
public:
    friction_layer();
    friction_layer(float l, float h  , std::array<float,2> p);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);
};

#endif // FRICTION_LAYER_H
