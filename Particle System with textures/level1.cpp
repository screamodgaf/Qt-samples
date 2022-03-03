#include "level1.h"
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>

Level1::Level1( )
{
    std::cout << "Level1() ctor" << "\n";
    sceneRect = QRectF(0,0,800,600); ///its needed for scene.update(rect) - to update and so items dont leave any artifacts
    this->setSceneRect(sceneRect);

    m_view = new QGraphicsView(this);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "game"));
    m_view->resize(800, 600);
    m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_view->setViewportUpdateMode(QGraphicsView::NoViewportUpdate );

    m_view->setScene(this);

    // a blue background
    m_view->setBackgroundBrush(Qt::black);
    m_view->show();

    //create items:
    tower = new Tower(this);
    //    enemy = new Enemy;

    player = new Player(this);
    player->setFlag(QGraphicsItem::ItemIsFocusable); ///only one item can respond to keyboard events
    player->setFocus();

    // player->setPos(player->mapToScene(30,500));
    //add to Scene
    this->addItem(tower);
    this->addItem(player);
    //set FPS counter stuff:
    setFPScounter();

    //periodic check if enemy within tower so it shoots every second and not every every frame:
    QTimer* towerAreaTimer = new QTimer();
    connect(towerAreaTimer, &QTimer::timeout, this,
            &Level1::checkTowersAreaPeriodicly);
    towerAreaTimer->start(700);

    //load qPixmap:
    QPixmap* pixmap1 = new QPixmap("E:\\Qt_workspace\\ShootingTower\\smoke4.png");
    //    pixmapItem = new QGraphicsPixmapItem;
    //    pixmapItem->setPixmap(*pixmap1);
    //    this->addItem(pixmapItem);

    //        QPainter pix(pixmap1);
    //        pix.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    //        pix.drawPixmap(pixmap1->rect()  , *pixmap1);
    //pix.set
    pixmap1->setDevicePixelRatio(0.5);

    QPainter pix(pixmap1);
    pix.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    //        pix.fillRect(pixmap1->rect(), QColor(0, 0, 0,  140)); // colorize the light in any /*color
    pix.drawPixmap(pixmap1->rect(), *pixmap1);
    pix.setRenderHints(QPainter::Antialiasing);




    //create particles:
    QPointF origin1 = {100, 100};
    particleSystem = new ParticleSystem(this, pixmap1, origin1);

    //    QPointF origin2 = {200, 70};
    //    fireParticleSystem = new FireParticleSystem(this, pixmap1, origin2);

    v_particleSystem.push_back(particleSystem);

    //    v_particleSystem.push_back(fireParticleSystem);




    ///add another particle system:
    QPixmap* pixmap2 = new QPixmap("E:\\Qt_workspace\\ShootingTower\\smoke6.png");
    pixmap2->setDevicePixelRatio(5);
    //create particles:
    QPointF origin2 = {150, 100};
    particleSystem2 = new ParticleSystem(this, pixmap2, origin2);
    v_particleSystem.push_back(particleSystem2);
    QPainter pix2(pixmap2);
    pix2.setCompositionMode(QPainter::CompositionMode_Multiply);
    //        pix.fillRect(pixmap1->rect(), QColor(0, 0, 0,  140)); // colorize the light in any /*color
    pix2.drawPixmap(pixmap2->rect(), *pixmap2);
    pix2.setRenderHints(QPainter::Antialiasing);




    //set gravity:
    gravity = {0,0.1};

    //initialize repeller:
    QVector2D rpos(170, 300);
    repeller = new Repeller(nullptr, &rpos);
    this->addItem(repeller);



}

void Level1::advance()
{
    countFPS();
    for (int i = 0; i < v_bullets.size(); ++i) {
        if(v_bullets[i]->checkBulletsDistFromTower(&v_bullets)){
            v_bullets.erase(std::remove(v_bullets.begin(), v_bullets.end(), v_bullets[i]), v_bullets.end());
            continue;
        }
        v_bullets[i]->update();
    }
    player->advance(1);

    //    QVector2D playerPos(player->pos().x(), player->pos().y());
    //    repeller->update(playerPos);




    for (int i = 0; i < v_particleSystem.size(); ++i) {
        v_particleSystem[i]->applyForce(gravity);

        QVector2D v = { (float)player->x(), (float)player->y() };
        repeller->update(v);
        //        repeller->setPos(player->x(), player->y());

        v_particleSystem[i]->applyReppeler(repeller);

        v_particleSystem[i]->addParticle();
        v_particleSystem[i]->run();
    }


    update(sceneRect); ///so items dont leave any artifacts though works without it when using m_view->viewport()->repaint();
    m_view->viewport()->repaint();
    //    player.passDelta(duration);countFPS();

}



void Level1::countFPS()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    start = std::chrono::high_resolution_clock::now();
    //    std::cout << "FPS: " <<  1/duration.count()  << "\n"; //1 second =    1000 milliseconds
    fpsLabel->setText("FPS: " + QString::number(int(1/duration.count())));

    ///if framerate is faster than 0.016 - wait untill it reaches 0.0163463 by entering while loop; "duration" in the the while loops condition insreases every iteration of the while iteration by the time the while iteration takes
    auto tstart = std::chrono::high_resolution_clock::now();  ///10
    while (duration.count() <  0.016) {   ///60 fps = 16 miliseconds cause 60*16 = 1000 so 0,016  sec = 16 miliseconds
        auto tend = std::chrono::high_resolution_clock::now(); ///20
        duration += tend-tstart; ///20 - 10 = 10 so while iteration took 10 | then we add the while iteration duration to framerate duration
    }

}



std::vector<Bullet *> *Level1::getBulletContainer()
{
    return &v_bullets;
}




void Level1::checkTowersAreaPeriodicly()
{
    if(tower->checkCollisionsWithAttackArea(player)){
        createBullet();
    }

}

void Level1::createBullet()
{
    Bullet* bullet = new Bullet(this, &v_bullets, tower);
    v_bullets.push_back(bullet);


    this->addItem(bullet); // this gives error/warning: "QGraphicsScene::addItem: item has already been added to this scene" - The usual way this happens is that when you create your QGraphicsItem you specify a parent for the item that is already in the scene. In this case there is no need to explicitly add it to the scene afterwards as the QGraphicsItem constructor does it for you if the parent is already in a scene.
    std::cout << "void Level1::keyPressEvent(QKeyEvent *event)" << "\n";
    bullet->estimateBulletTrajectory(tower, player);
    bullet->setRotationTowardTarget(tower, player);
    update(sceneRect); ///so items dont leave any artifacts though works without it when using m_view->viewport()->repaint();

}


void Level1::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_B){
        createBullet();
    }

    if(event->key() == Qt::Key::Key_Up || event->key() == Qt::Key::Key_Down ||
            event->key() == Qt::Key::Key_Left || event->key() == Qt::Key::Key_Right)
        player->keyPressEvent(event);


}

void Level1::setFPScounter()
{
    fpsLabel = new QLabel(m_view);
    fpsLabel->setGeometry(5,5, 60, 20); // so not only the first char appears - it must be widened
    fpsLabel->setStyleSheet("QLabel { color : lime; font-size: 15px;}");
    fpsLabel->show();

    timeElapsed = std::chrono::microseconds(0);
    start = std::chrono::high_resolution_clock::now();
}
