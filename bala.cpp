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
    painter->drawPixmap(-lx/2,-ly/2,*pixmap,0,0,lx,ly);
}

bala::bala(float ra, std::array<float, 2> p, std::array<float, 2> v)
{
    mass=0;
    ace[0]=0;
    ace[1]=0;
    vel=v;
    pos=p;
    lx=20;
    ly=20;
    setPos(pos[0],-pos[1]);
    pixmap= new QPixmap(":/images/bala.png");

}
