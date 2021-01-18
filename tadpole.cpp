#include "tadpole.h"

tadpole::tadpole()
{

}

void tadpole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(boundingRect());
}

tadpole::tadpole(float rad, float ay, std::array<float, 2> p, std::array<float, 2> v)
{
    mass=0;
    ace[0]=0;
    ace[1]=ay;
    vel=v;
    pos=p;
    lx=rad;
    ly=rad;
    setPos(pos[0],-pos[1]);
}
