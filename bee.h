#ifndef BEE_H
#define BEE_H
#include "base.h"
#include <QTimer>
#include <QObject>


class bee : public base
{
private:
    float r;
    float time;
public:
    bee();
    bee(float rad, float ra, std::array<float,2> p, float vx);
    void Advance(float t);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr);
    int columnas,filas;
    QPixmap *pixmap;
    int c;
};

#endif // BEE_H
