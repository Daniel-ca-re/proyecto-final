#include "tong.h"
#include "math.h"


tong::tong()
{

}

tong::tong(float ra, std::array<float, 2> p, float vx)
{
    mass=10;
    ace[0]=0;
    ace[1]=0;
    vel[0]=vx;
    vel[1]=0;
    pos=p;
    lx=ra;
    ly=ra/2;
    setPos(pos[0],-pos[1]);
    k=2;
    A=sqrt(mass*k)*vx;
    w=sqrt(k/mass);
    time=0;
    posi=pos;
}

void tong::Advance(float t)
{
    t/=25;
    time+=t;
    pos[0]=posi[0]+A*sin(w*time);
    setPos(pos[0],-pos[1]);

}

void tong::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::magenta);
    painter->drawEllipse(boundingRect());
}

char tong::where_is_it(std::array<float, 2> p)
{
    if (p[0]<pos[0])
    {
       return 'a';
    }
    else if(p[0]>pos[0])
    {
        return 'd';
    }

}
