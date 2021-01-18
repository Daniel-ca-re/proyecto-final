#include "base.h"
#include <cmath>

base::base()
{

}
base::base(float m, float x,float y, std::array<float, 2> p, std::array<float, 2> v)
{
    mass=m;
    ace[0]=0;
    ace[1]=0;
    vel=v;
    pos=p;
    lx=x;
    ly=y;
    setPos(pos[0],-pos[1]);
}


std::array<float, 2> base ::getvel()
{
    return vel;
}

std::array<float, 2> base::getpos()
{
    return pos;
}
std::array<float, 2> base::getace()
{
    return ace;
}
float base::getmass()
{
    return mass;
}

float base::getrad()
{
    return lx;
}

void base::setmass(float m)
{
    mass=m;
}

void base::setpos(float x, float y)
{
    pos={x,y};
    setPos(x,-y);
}

void base::setvel(float x, float y)
{
    vel[1]=y;
    vel[0]=x;
}

void base::setace(float x, float y)
{
    ace[1]=y;
    ace[0]=x;
}

void base::setacewithforce(std::array<float,2> force)
{
    ace[1]=force[1]/mass;
    ace[0]=force[0]/mass;
}

void base::Advance(float t)
{
    pos[0]+=vel[0]*t+(ace[0]/2)*pow(t,2);
    pos[1]+=vel[1]*t+(ace[1]/2)*pow(t,2);
    vel[0]+=ace[0]*t;
    vel[1]+=ace[1]*t;
    setPos(pos[0],-pos[1]);
}

QRectF base::boundingRect() const
{
    return QRectF(-lx/2,-ly/2,lx,ly);
}

void base::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setBrush(Qt::blue);
        painter->drawEllipse(boundingRect());

}
