#include "particle.h"
#include <QPen>
#include <QPainter>
#include <ctime>
#include <iostream>
Particle::Particle()
{
    rect.setSize(QSizeF(30,30));

    //generate random float:

    float min = -1;
    float max = 1;
    float r = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    float r1 = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));

    vel = {r, r1 };
    acc = {0, 0.02};
    pos = {400,50};
    this->setPos(pos.x(), pos.y());

    lifespan = 1;
}


void Particle::update()
{


    vel += acc;
    pos += vel;

    //limit velocity if its too large
    //    if( abs(vel.x()) > 20){
    //        vel.setX(vel.x()/2);
    //        vel.setY(vel.y()/2);
    //    }
    this->setPos(pos.x(), pos.y());
//    vel = {0,0}; ///reseting velocity to 0
    lifespan-=0.005;
}

QRectF Particle::boundingRect() const
{
    return rect;
}

void Particle::advance(int phase)
{

}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();


    QColor white = Qt::white;
    if(lifespan>=0)
        white.setAlphaF(lifespan); ///qreal alpha is specified in the range 0.0-1.0.
    painter->setBrush(white);
    painter->setPen(Qt::transparent);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(rect);
    //    std::cout << "vel: " << vel.x() << "\n";
}

bool Particle::is_finished()
{
    if(lifespan<=0)
        return true;
    else
        return false;
}

Particle::~Particle()
{
    std::cout << "particle DESTROYED" << "\n";
}
