#ifndef LEVEL1_H
#define LEVEL1_H
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include <QGraphicsLineItem>
#include "player.h"
#include <QKeyEvent>
#include <vector>
#include <QLabel>
#include <QElapsedTimer>

#include "Particles/particlesystem.h"
#include "Particles/fireparticlesystem.h"
#include "Particles/repeller.h"

class Level1 : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Level1();
    virtual void keyPressEvent(QKeyEvent *event);
    void setFPScounter();
    void countFPS();

    static std::vector<Bullet*> *getBulletContainer();


public slots:
    void advance();
    void checkTowersAreaPeriodicly();

    //    void update(const QRectF &rect = QRectF());
signals:
private:
    void createBullet();
private:
    QGraphicsView* m_view;
    Tower* tower;
    Player* player;


    QRectF sceneRect;
    static  std::vector<Bullet*> v_bullets;
    QLabel* fpsLabel;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end ;
    std::chrono::duration<float> duration, timeElapsed;


    QGraphicsPixmapItem* pixmapItem;
    ParticleSystem* particleSystem;
    ParticleSystem* particleSystem1;
    ParticleSystem* particleSystem2;
    FireParticleSystem* fireParticleSystem;
    std::vector<ParticleSystem*> v_particleSystem;

    QVector2D gravity;
    Repeller* repeller;
};

#endif // LEVEL1_H
