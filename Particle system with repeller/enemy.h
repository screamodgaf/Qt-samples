#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class Enemy : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
signals:
private:
    QRectF rect;

};

#endif // ENEMY_H
