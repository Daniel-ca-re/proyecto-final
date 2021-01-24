#include "frog.h"

frog::frog()
{

}

void frog::Advance(float t)
{
    lengua->Advance(t);
}

void frog::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(boundingRect());
}

void frog::setlife(int vida)
{
    life=vida;
}

void frog::gethit(int golpe)
{
    life-=golpe;
}

frog::frog(float ra, std::array<float, 2> p, float vx)
{
    mass=0;
    ace[0]=0;
    ace[1]=0;
    vel[0]=0;
    vel[1]=0;
    pos=p;
    lx=ra;
    ly=ra;
    setPos(pos[0],-pos[1]);
    p[1];
    lengua=new tong(ra/2, p, vx);
    life=30;
}
