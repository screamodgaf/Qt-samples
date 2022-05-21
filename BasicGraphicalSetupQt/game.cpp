#include "game.h"
#include <iostream>
#include <QKeyEvent>
Game::Game()
{
    m_view = new QGraphicsView(this);
    m_view->setSceneRect(QRectF(0,0,8000000, 8000000));

    gl = new QOpenGLWidget(m_view);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);

    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setSwapBehavior(QSurfaceFormat::TripleBuffer);
    format.setSwapInterval(1);
    format.setSamples(4);
    gl->setFormat(format);
    m_view->setViewport(gl);
    //opengl end

    m_view->setScene(this);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "game"));
    m_view->resize(800, 600);
    m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform  | QPainter::LosslessImageRendering | QPainter::TextAntialiasing);
    m_view->setViewportUpdateMode(QGraphicsView::NoViewportUpdate );
    m_view->setCacheMode(QGraphicsView::CacheBackground);
    m_view->setBackgroundBrush(Qt::black);
    m_view->show();

    player = new Player;
    player->setPos(200,300);
    player->setZValue(10);
    this->addItem(player);

    target = new QGraphicsRectItem();
    target->setRect(0,0,30,30);
    target->setBrush(Qt::red);
    target->setPos(500,400);
    target->setTransformOriginPoint(target->boundingRect().center());
    target->setFlag(QGraphicsItem::ItemIsFocusable);
    this->addItem(target);
}

float maxSpeed = 2.f;
float maxForce = 0.02; ///how sharp the turns are

void Game::advance()
{
    QVector2D desiredVel = QVector2D(target->pos() - player->pos());
    ///setting magnitude to maxSpeed (normalizing to length 1 and scaled by multiplying by maxSpeed)
    desiredVel.normalize();
    desiredVel *= maxSpeed;
    ///Reynolds formula:
    QVector2D steering = desiredVel - player->getVelocity();
    ///limit force by setting maximum force to maxForce:
    steering.normalize();
    steering *= maxForce;

    player->applyForce(steering);


    player->advance();
    update();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Left:
        target->moveBy(-7,0);
        break;
    case Qt::Key_Right:
        target->moveBy(7,0);
        break;
    case Qt::Key_Up:
        target->moveBy(0, -7);
        break;
    case Qt::Key_Down:
        target->moveBy(0, 7);
        break;
    case Qt::Key_Q:
        target->setRotation(target->rotation() -3);
        break;
    case Qt::Key_W:
        target->setRotation(target->rotation() +3);
        break;
    }
    update();
}

Game::~Game()
{
    qDebug() << "~Game";
    delete player;
    player = nullptr;
    delete target;
    target = nullptr;
    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
}
