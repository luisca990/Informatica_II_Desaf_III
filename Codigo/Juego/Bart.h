#ifndef BART_H
#define BART_H
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
    int spriteX = 8;//0;
    int spriteY = 54;
    int spriteAncho = 24;
    int spriteAlto = 50;
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
    void confSprite(int dir,int dirX);

public slots:
    void movContinuo();

signals:
    void llegarBorde();

};

#endif // BART_H
