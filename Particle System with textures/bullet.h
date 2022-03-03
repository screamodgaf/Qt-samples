#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QVector2D>
#include <vector>
class Bullet:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(QGraphicsScene *scene, std::vector<Bullet*>* v_bullets, QGraphicsItem *parent = nullptr);
    ~Bullet();
    void estimateBulletTrajectory(QGraphicsItem *origin, QGraphicsItem *target);
    void setRotationTowardTarget(QGraphicsItem *origin_, QGraphicsItem *target);
    void update();

    QRectF boundingRect() const override;
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;


    bool checkBulletsDistFromTower(std::vector<Bullet *> *v_bullets);
signals:
    emit void deleteBullet(Bullet*);
private:
    QRectF rect;
    QGraphicsItem *origin; //tower
    QVector2D pos;
    QVector2D vel;
    QVector2D acc;

    float orginWidth;
    float orginHight;
    float targetWidth;
    float targetHight;

    QGraphicsLineItem line;



};

#endif // BULLET_H
