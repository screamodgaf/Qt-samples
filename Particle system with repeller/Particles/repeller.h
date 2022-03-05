#ifndef REPELLER_H
#define REPELLER_H
#include <QGraphicsItem>
#include <QVector2D>
#include "Particles/particle.h"
class Repeller: public QGraphicsItem
{
public:
    explicit Repeller(QGraphicsItem* parent = nullptr, QVector2D* position = nullptr);
    void update(QVector2D &position);
    QRectF boundingRect() const override;
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    QVector2D repel(Particle *p);
protected:
    QVector2D pos;
    QVector2D vel;
    QVector2D acc;
    QRectF rect;
    QPointF m_origin;
};

#endif // REPELLER_H
