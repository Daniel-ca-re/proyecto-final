#ifndef PLATFORM_H
#define PLATFORM_H
#include "friction_layer.h"
#include <QGraphicsItem>


class platform : public friction_layer
{
private:

public:
    friction_layer* fake_layer;
    platform();
    platform(float l, float h  , std::array<float,2> p, std::array<float,2> v, char t);
    void Advance(float t);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);
    char where_is_it(std::array<float, 2> p);
    float H;
    char type;
    float L;
    QPixmap *suelo;
    QPixmap *agua;
    QRectF boundingRect() const;
};

#endif // PLATFORM_H
