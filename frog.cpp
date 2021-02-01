#include "frog.h"

frog::frog()
{

}

void frog::Advance(float t)
{
    lengua->Advance(t);
    lengua2= new platform(-lengua->getpos()[0]+pos[0],6,{lengua->getpos()[0],lengua->getpos()[1]+3},{0,0},'t');
    sprintstate();
    this->update(-lx/2,-ly/2,lx,ly);
}

void frog::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-lx/2,-ly/2,*pixmap,columnas,filas,lx,ly);
}

void frog::setlife(int vida)
{
    life=vida;
}

void frog::gethit(int golpe)
{
    life-=golpe;
}

void frog::sprintstate()
{
    if(pos[0] < lengua->getpos()[0])
    {
        filas=0;
        columnas=0*lx;
    }
    else
    {
        filas=0;
        columnas=1*lx;
    }
}

frog::frog(float ra, std::array<float, 2> p, float vx)
{
    mass=0;
    ace[0]=0;
    ace[1]=0;
    vel[0]=0;
    vel[1]=0;
    pos=p;
    lx=3*51;
    ly=3*55;
    setPos(pos[0],-pos[1]);
    p[1];
    lengua=new tong(lx/2, p, vx);
    life=40;
    lengua2= new platform(lengua->getpos()[0]-pos[0],2,lengua->getpos(),{0,0},'t');
    pixmap = new QPixmap(":/images/frog.png");
}
