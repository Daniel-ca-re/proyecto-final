#include "bala.h"

bala::bala()
{

}

QRectF bala::boundingRect() const
{
        return QRectF(-lx/2,-ly/2,lx,ly);
}

void bala::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(boundingRect());
}

bala::bala(float ra, std::array<float, 2> p, std::array<float, 2> v)
{
    mass=0;
    ace[0]=0;
    ace[1]=0;
    vel=v;
    pos=p;
    if(v[1]==0)
    {
        lx=2*ra;
        ly=ra;
    }
    else
    {
        lx=ra;
        ly=2*ra;
    }
    setPos(pos[0],-pos[1]);
}
