#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class Tower : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Tower(QGraphicsScene* scene, QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    bool checkCollisionsWithAttackArea(QGraphicsItem* item);
signals:
private:
    QRectF rect;
    QGraphicsEllipseItem* attackArea;

};

#endif // TOWER_H



