#include "bee.h"
#include "cmath"

bee::bee()
{

}

void bee::Advance(float t)
{
    time+=t;
    pos[0]+=vel[0]*t;
    setPos(int(r*cos(time/5)+pos[0]),-int(r*sin(time/5)+pos[1]));
}

void bee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
}

bee::bee(float rad, float ra, std::array<float,2> p, float vx)
{
    mass=0;
    ace[0]=0;
    ace[1]=0;
    vel[0]=vx;
    vel[1]=0;
    pos=p;
    lx=ra;
    ly=ra;
    setPos(pos[0],-pos[1]);
    r=rad;
    time=0;
}
