#ifndef JUGADOR_H
#define JUGADOR_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsView>
#include <QTimer>

class Jugador:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x = 200;
    qreal y = 200;
    int spriteX = 0;
    int spriteY = 0;
    int spriteAncho = 60;
    int spriteAlto = 60;
    QPixmap hojaSprites;
    QPixmap sprite;
    int cont=0;
    QSize limites;
    QTimer *timerMov;
    int dx, dy;
    QGraphicsView *vista;

public:
    Jugador(QGraphicsView *vista);
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void confSprite(int dir);

public slots:
    void movContinuo();

signals:
    void llegarBorde();

};

#endif // JUGADOR_H
