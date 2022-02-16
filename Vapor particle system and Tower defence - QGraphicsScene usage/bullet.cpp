#include "bullet.h"
#include "level1.h"
#include <cmath>
#include <QDebug>
#include <iostream>

Bullet::Bullet(QGraphicsScene *scene, std::vector<Bullet *> *v_bullets, QGraphicsItem *parent)  /*: QGraphicsItem{parent}*/

{

    rect.setSize(QSizeF(30,2 ));
    vel = {0,0};
    acc = {0,0};
    float parWidth = parent->boundingRect().width();
    float parHight = parent->boundingRect().height();
    pos = {(float)parent->x() + parWidth/2, (float)parent->y() + parHight/2};


    //    pos = {0 + parWidth/2, 0 + parHight/2};  //set position toward parent (was {0,0}) so its in parents centre
    this->setX(pos.x());
    this->setY(pos.y());

}


//tower, player, this);
void Bullet::estimateBulletTrajectory(QGraphicsItem* origin, QGraphicsItem* target)
{
    QPen pen(Qt::DashDotLine);
    pen.setColor(Qt::red);
    orginWidth = origin->boundingRect().width();
    orginHight = origin->boundingRect().height();
    targetWidth = target->boundingRect().width();
    targetHight = target->boundingRect().height();

    ///draws line from tower CENTRE (+targetWidth/2 for centering) to target's CENTRE:
    //setting QLineF:
    QLineF ln;
    ln.setP1(QPointF(target->pos().x() + targetWidth/2,
                     target->pos().y() + targetHight/2));
    ln.setP2(QPointF(origin->scenePos().x() + orginWidth/2,
                     origin->scenePos().y() + orginHight/2));

    line.setLine(ln);
    line.setPen(pen);
    this->scene()->addItem(&line); //drawing
//    m_scene->addItem(&line); //drawing
    ///acceleration (normalized vector) from origin to target to add to velocity every frame so bullet heads toward target
    ///acc.setX(ln.p1().rx() - ln.p2().rx()); //works too instead of acc.setX((target->x() + targetWidth/2) - (origin->x() + orginWidth/2));
    ///acc.setY(ln.p1().ry() - ln.p2().ry()); //works too works too instead of acc.setY((target->y() + targetHight/2) - (origin->y() + orginHight/2));


    acc.setX((target->x() + targetWidth/2) - (origin->x() + orginWidth/2));
    acc.setY((target->y() + targetHight/2) - (origin->y() + orginHight/2));

    acc.normalize();
}
void Bullet::setRotationTowardTarget(QGraphicsItem *origin_, QGraphicsItem *target)
{
    origin = origin_;
    QVector2D distBetweenPoints((target->x() + targetWidth/2) - (origin->x() + orginWidth/2),  /// +orginWidth/2 so bullet wont lose trajectory
                                (target->y() + targetHight/2) - (origin->y() + orginHight/2));

    double rad = std::atan2(distBetweenPoints.y(), distBetweenPoints.x());
    double degrees =  rad* 180.0 /M_PI;
    this->setRotation( degrees );
    return;
}

void Bullet::update()
{
//    checkBulletsDistFromTower();

    vel += acc;
    pos += vel;

    //limit velocity if its too large
    //    if( abs(vel.x()) > 20){
    //        vel.setX(vel.x()/2);
    //        vel.setY(vel.y()/2);
    //    }
    this->setPos(pos.x(), pos.y());
    vel = {0,0};


}



QRectF Bullet::boundingRect() const
{
    return rect;
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPen bullet(Qt::red, 6);
    bullet.setStyle(Qt::DotLine);
    painter->setPen(bullet);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(rect);
}



bool Bullet::checkBulletsDistFromTower(std::vector<Bullet*>* v_bullets)
{
    QLineF ln;
    ln.setP1(QPointF(this->x(), this->y()));
    ln.setP2(QPointF(origin->scenePos().x() + orginWidth/2,
                     origin->scenePos().y() + orginHight/2));
//    std::cout << "ln.length(): " << ln.length() << "\n";

//    std::cout << "origin->boundingRect().width()L " << origin->boundingRect().width() << "\n";
    if(ln.length() >= origin->boundingRect().width()*4){
            this->scene()->removeItem(this);
            delete this;
        return true;
        //        scene()->removeItem(this);
       ///remove this bullet from m_v_Bullets - container that has all Bullets inside, so we wont hit nullpointer

    }
    return false;
}

void Bullet::advance(int phase)
{
    std::cout << "void Bullet::advance(int phase)" << "\n";
}

Bullet::~Bullet()
{

    std::cout << "BULLET destroyed ~Bullet()" << "\n";
}
