#include "angry_bee.h"
#include "cmath"

angry_bee::angry_bee()
{

}

void angry_bee::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-lx/2,-ly/2,*pixmap,columnas,filas,lx,ly);
}

void angry_bee::set_sprite(float px)
{
    if(pos[0]<px)
    {
        filas=1*25;
    }
    else
    {
        filas=0;
    }
}

void angry_bee::Advance(float t, std::array<float, 2> p)
{
    float h=sqrt(pow(p[0]-pos[0],2)+pow(p[1]-pos[1],2));
    vel[0]=((p[0]-pos[0])/h)*v;
    vel[1]=((p[1]-pos[1])/h)*v;
    pos[0]+=vel[0]*t;
    pos[1]+=vel[1]*t;
    setPos(pos[0],-pos[1]);
    if((++c)%2==0)
    {
        columnas=(int(lx)+columnas)%112;
    }
    set_sprite(p[0]);
    this->update(-lx/2,-ly/2,lx,ly);
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
    lx=28;
    ly=25;
    setPos(pos[0],-pos[1]);
    columnas=0;
    filas=0;
    pixmap= new QPixmap(":/images/Abee.png");
}

