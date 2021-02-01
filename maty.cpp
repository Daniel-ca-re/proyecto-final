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
    painter->drawPixmap(-lx/2,-ly/2,*pixmap,columnas,filas,lx,ly);
}

void maty::sprintstate()
{
    if (vel[1]>0)
    {
        columnas=0;
        filas=0;
    }
    else if (vel[1]<-1)
    {
        columnas=1*lx;
        filas=0;
    }
    else if (vel[0]>0)
    {
        columnas=0*lx;
        filas=2*ly;
    }
    else if (vel[0]<0)
    {
        columnas=1*lx;
        filas=2*ly;
    }
    else
    {
        columnas=0;
        filas=1*ly;
    }
}

void maty::Advance(float t)
{
    base::Advance(t);
    sprintstate();
    this->update(-lx/2,-ly/2,lx,ly);
}

maty::maty(float d, float h, std::array<float, 2> p, float ay)
{

    lx=27*2;
    ly=36*2;
    pos=p;
    ace[0]=0;
    ace[1]=ay;
    setPos(pos[0],-pos[1]);
    vel={0,0};
    ry=ly/2;
    rx=lx/2;
    life=100;
    columnas=0;
    filas=1*ly;
    pixmap= new QPixmap(":/images/tarzan_png.png");
}
