#ifndef TONG_H
#define TONG_H
#include "base.h"


class tong : public base
{
private:
    float k;
    float A;
    float w;
    float time;
    std::array<float,2> posi;
public:
    tong();
    tong(float ra, std::array<float,2> p, float vx);
    void Advance(float t);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);
    char where_is_it(std::array<float, 2> p);

};

#endif // TONG_H
