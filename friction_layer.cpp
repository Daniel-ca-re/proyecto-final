#include "friction_layer.h"

friction_layer::friction_layer()
{

}

QRectF friction_layer::boundingRect() const
{
    return QRectF(pos[0]/100000,-pos[1]/100000,lx,ly);
}

void friction_layer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());

}
friction_layer::friction_layer(float l, float h, std::array<float, 2> p)
{
    pos=p;
    lx=l;
    ly=h;
}
