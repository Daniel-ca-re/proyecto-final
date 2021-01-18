#include "platform.h"

platform::platform()
{

}

void platform::Advance(float t)
{
    friction_layer::Advance(t);
    fake_layer->setpos(pos[0],pos[1]+3);
}

void platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (type=='w')
    {
        painter->setBrush(Qt::blue);
        painter->drawRect(boundingRect());
    }
    else if(type=='g')
    {
        painter->setBrush(Qt::green);
        painter->drawRect(boundingRect());
    }
}

char platform::where_is_it(std::array<float, 2> p)
{
    if (p[0]<pos[0])
    {
       return 'a';
    }
    else if(p[0]>pos[0]+lx)
    {
        return 'd';
    }
    else
    {
        if(p[1]>=pos[1])
        {
            return 'w';
        }
        else
        {
            return 's';
        }

    }
}

platform::platform(float l, float h, std::array<float, 2> p, std::array<float, 2> v, char t)
{
    pos=p;
    vel=v;
    lx=l;
    ly=h;
    setPos(pos[0],-pos[1]);
    p[1]+=3;
    fake_layer = new friction_layer(l,3,p);
    type=t;
    H=h;

}
