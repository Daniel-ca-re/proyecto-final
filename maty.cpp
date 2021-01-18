#include "maty.h"

maty::maty()
{

}

void maty::up()
{
    vel[1]+=vy;
}

void maty::down()
{
    if(vel[1]>0)
    {
        vel[1]=0;
    }
}

void maty::right()
{
    if(vel[0]<10)
    {
        vel[0]+=vx;
    }
}

void maty::left()
{
    if(vel[0]>-10)
    {
        vel[0]-=vx;
    }
}

void maty::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkYellow);
    painter->drawEllipse(boundingRect());
}

maty::maty(float d, float h, std::array<float, 2> p, float ay)
{

    lx=d;
    ly=h;
    pos=p;
    ace[0]=0;
    ace[1]=ay;
    setPos(pos[0],-pos[1]);
    vel={0,0};
    ry=ly/2;
}
