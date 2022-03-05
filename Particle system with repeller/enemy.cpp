#include "enemy.h"

Enemy::Enemy(QObject *parent)
    : QObject{parent}
{
    rect.setSize(QSizeF(50,50));
//    rect.setRect(0,0,50,50);

}

QRectF Enemy::boundingRect() const
{
    return rect;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPen pen(Qt::green, 3);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(rect);
}

void Enemy::advance(int phase)
{

}
