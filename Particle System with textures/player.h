#ifndef PLAYER_H
#define PLAYER_H
#include <QPainter>
#include <QObject>
#include <QKeyEvent>
#include <QGraphicsItem>
class Player : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr); 
protected:
    void advance(int step) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    QRectF boundingRect() const override; //pure virtual public function - When writing a custom graphics item, you must implement QGraphicsItem's two pure virtual public functions: boundingRect(), which returns an estimate of the area painted by the item, and paint(), which implements the actual painting. In addition, we reimplement the shape() and advance().

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, //pure virtual public function
               QWidget *widget) override;


    void update(const QRectF &rect = QRectF());
private:
    void checkCollisions();
private:
    float speed;
    QColor color;
    bool is_moving_left ;
    bool is_moving_right;
    bool is_moving_up   ;
    bool is_moving_down ;

    QRectF rect;
    QRectF rectPast;
    QPainter* m_painter = nullptr;


    std::vector<QGraphicsItem*> v_itemsInCollisionWithPlayer;

    qreal old_x;
    qreal old_y;
    qreal oldScene_x;
    qreal oldScene_y;

    bool is_draw;
    bool is_sceneChanged;

    QRectF pastRect;
    QPainter *preCollisionPainter = nullptr;

    friend class Level1;

signals:

};

#endif // PLAYER_H
