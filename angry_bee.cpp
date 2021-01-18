#include "angry_bee.h"
#include "cmath"

angry_bee::angry_bee()
{

}

void angry_bee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());
}

void angry_bee::Advance(float t, std::array<float, 2> p)
{
    float h=sqrt(pow(p[0]-pos[0],2)+pow(p[1]-pos[1],2));
    vel[0]=((p[0]-pos[0])/h)*v;
    vel[1]=((p[1]-pos[1])/h)*v;
    pos[0]+=vel[0]*t;
    pos[1]+=vel[1]*t;
    setPos(pos[0],-pos[1]);
}

angry_bee::angry_bee(float ra, std::array<float, 2> p, float V)
{
    v=V;
    mass=0;
    ace[0]=0;
    ace[1]=0;
    vel[0]=0;
    vel[1]=0;
    pos=p;
    lx=ra;
    ly=ra;
    setPos(pos[0],-pos[1]);
}

