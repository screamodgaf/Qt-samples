#include "repeller.h"
#include <QPainter>
#include <iostream>
#include <algorithm>
#include <QObject>
Repeller::Repeller(QGraphicsItem *parent, QVector2D *position): QGraphicsItem{parent}
{
    rect.setSize(QSizeF(40,40));
    if(position){
        pos = *position;
        this->setPos(pos.x(), pos.y());
    }else
        this->setPos(parent->x(), parent->y());
}

void Repeller::update(QVector2D& position)
{
    this->setPos(position.x(), position.y());
    pos = position;
}

QRectF Repeller::boundingRect() const
{
    return rect;
}

void Repeller::advance(int phase)
{

}

void Repeller::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QColor red = Qt::blue;
    //    if(lifespan>=0)
    //        red.setAlphaF(lifespan); ///qreal alpha is specified in the range 0.0-1.0.
    painter->setBrush(red);
    painter->setPen(Qt::transparent);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(rect);
}

QVector2D Repeller::repel(Particle *p)
{
    //    std::cout << "repel" << "\n";
    QVector2D repPos(this->pos.x(), this->pos.y());
    QVector2D particlePos(p->x(), p->y());
    QVector2D dir = repPos - particlePos;

    float d = dir.length(); ///magnitude of a vector is the length of the vector.
    d = std::clamp(d,  5.f, 100.f);
    dir.normalize();

    float force = -1  * 412.1  / (d*d);
    dir*= force;
    //// gravity = {0,0.1};

    return dir;
}
