#ifndef TADPOLE_H
#define TADPOLE_H
#include "base.h"


class tadpole : public base
{
public:
    tadpole();
    tadpole(float rad,float ay, std::array<float, 2> p, std::array<float, 2> v);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TADPOLE_H
