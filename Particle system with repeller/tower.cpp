#include "tower.h"
#include "level1.h"
#include <iostream>
Tower::Tower(QGraphicsScene *scene, QObject *parent)  : QObject{parent}
{

    //  rect.setRect(0,0, 50,50); //bounding rect
    rect.setSize(QSizeF(50,50));
    this->setPos(scene->width()/2  - rect.width()/2,
                 scene->height()/2 - rect.height()/2);

    //setting area within which the tower shoots bullets:
    attackArea = new QGraphicsEllipseItem(this);

    QSizeF attAreaSize(400.f,400.f);
    attackArea->setRect(QRectF(this->x() - attAreaSize.width()/2 + rect.width()/2,
                               this->y() - attAreaSize.width()/2 + rect.height()/2,
                               attAreaSize.width(), attAreaSize.height()));
    scene->addItem(attackArea);

}

QRectF Tower::boundingRect() const
{
    return rect;
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QPen towerPen(Qt::red, 3);
    painter->setPen(towerPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(rect);

    QPen attackAreaPen(QColor(255,20,147), 3);
    attackArea->setPen(attackAreaPen);
    painter->setPen(attackAreaPen);
    painter->setRenderHint(QPainter::Antialiasing);


}

bool Tower::checkCollisionsWithAttackArea(QGraphicsItem *item)
{
    if(attackArea->collidesWithItem(item)){
        std::cout << "attackArea->collidesWithItem(item)" << "\n";
        return true;
    }

}

void Tower::advance(int phase)
{

}
