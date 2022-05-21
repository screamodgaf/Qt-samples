#include "player.h"
#include <iostream>
Player::Player()
{
    rect.setRect(0,0,30,30);
    loc = {10.f ,10.f };
    vel = {0.f ,0.f };
    acc = {0.f ,0.f };
}

void Player::applyForce(QVector2D& force)
{
    acc += force;
}

void Player::advance()
{
    vel += acc;
    loc += vel;
    this->setPos(loc.x(), loc.y());

    acc = {0.f,0.f};
    //    vel = {0.f,0.f};
}

QVector2D Player::getVelocity()
{
    return vel;
}

QRectF Player::boundingRect() const
{
    return rect;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::green);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(rect);
}

Player::~Player()
{
    qDebug() << "~Player()";
}
