#ifndef PARTICLE_H
#define PARTICLE_H

#include <QGraphicsItem>
#include <QObject>
#include <QVector2D>
#include <QGraphicsPixmapItem>
class Particle : public QGraphicsPixmapItem
{

public:
    Particle(QPixmap* pixmap, QPointF& origin);
    ~Particle();
    void update();

    void advance(int phase) override;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    bool is_finished();
    void applyForce(QVector2D& force);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVector2D pos;
    QVector2D vel;
    QVector2D acc;
    float lifespan;

    QRectF rect;
    QPointF m_origin;
    QPixmap *m_pixmap;

};

#endif // PARTICLE_H
