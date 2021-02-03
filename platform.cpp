#include "platform.h"

platform::platform()
{

}

void platform::Advance(float t)
{
    base::Advance(t);
    fake_layer->setpos(pos[0],pos[1]+3);
    this->update(0,0,lx,ly);
}

void platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (type=='w')
    {
        painter->drawPixmap(0,0,*agua,0,0,lx,ly);
    }
    else if(type=='g')
    {
        painter->drawPixmap(0,0,*suelo,0,0,lx,ly);
    }
    else
    {
        painter->setBrush(Qt::magenta);
        painter->drawRect(friction_layer::boundingRect());
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

QRectF platform::boundingRect() const
{
    return QRectF(0,0,lx,ly);
}

platform::platform(float l, float h, std::array<float, 2> p, std::array<float, 2> v, char t)
{
    pos=p;
    vel=v;
    lx=l;
    ly=10;
    setPos(pos[0],-pos[1]);
    p[1]+=3;
    fake_layer = new friction_layer(l,3,p);
    ace={0,0};
    type=t;
    H=h;
    L=l;
    fake_layer->setpos(pos[0],pos[1]+3);
    suelo= new QPixmap(":/images/suelo.png");
    agua= new QPixmap(":/images/agua.png");

}
