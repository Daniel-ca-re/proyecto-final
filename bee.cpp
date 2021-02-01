#include "bee.h"
#include "cmath"

bee::bee()
{

}

void bee::Advance(float t)
{
    if((++c)%2==0)
    {
        columnas=(int(lx)+columnas)%104;
    }
    time+=t;
    pos[0]+=vel[0]*t;
    setPos(int(r*cos(time/5)+pos[0]),-int(r*sin(time/5)+pos[1]));
    this->update(-lx/2,-ly/2,lx,ly);
}

void bee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-lx/2,-ly/2,*pixmap,columnas,filas,lx,ly);
}


bee::bee(float rad, float ra, std::array<float,2> p, float vx)
{
    mass=0;
    ace[0]=0;
    ace[1]=0;
    vel[0]=vx;
    vel[1]=0;
    pos=p;
    lx=104/4;
    ly=25;
    setPos(pos[0],-pos[1]);
    r=rad;
    time=0;
    columnas=0;
    filas=0;
    pixmap= new QPixmap(":/images/bee.png");

}
