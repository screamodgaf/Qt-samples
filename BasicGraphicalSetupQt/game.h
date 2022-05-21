#ifndef GAME_H
#define GAME_H
#include "player.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QOpenGLWidget>
#include <QGraphicsRectItem>

class Game : public QGraphicsScene
{
public:
    Game();
    ~Game();
    void keyPressEvent(QKeyEvent* event);
    void advance();
private:
    Player* player = nullptr;
    QGraphicsRectItem* target = nullptr;
    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;
};

#endif // GAME_H
