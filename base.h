#ifndef BASE_H
#define BASE_H
#include <QGraphicsItem>
#include <QPainter>
#include <array>


class base: public QGraphicsItem
{
protected:

    float mass;
    std::array <float,2> pos;
    std::array <float,2> vel;
    std::array <float,2> ace;
    float lx;
    float ly;
public:
    base();
    base(float m, float x,float y, std::array<float, 2> p, std::array<float, 2> v);
    std::array <float,2> getpos();
    std::array <float,2> getvel();
    std::array <float,2> getace();
    float getmass();
    float getrad();
    void setmass(float);
    void setpos(float x,float y);
    void setvel(float x,float y);
    void setacewithforce(std::array<float,2> force);
    void setace(float x, float y);
    void Advance(float t);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);




public slots:

};

#endif // BASE_H
