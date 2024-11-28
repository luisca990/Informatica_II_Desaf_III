#ifndef BART_H
#define BART_H
#include "personaje.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsView>
#include <QTimer>

class Bart:public QObject, public QGraphicsPixmapItem,public Personaje
{
    Q_OBJECT

private:
    qreal x = 2;
    qreal y = 476;
    int spriteX = 8;//0;
    int spriteY = 54;
    int spriteAncho = 24;
    int spriteAlto = 50;
    float velocidadX = 0.0f; // Velocidad horizontal de Bart
    float velocidadY = 0.0f; // Velocidad vertical de Bart
    float coefFriccion = 0.02f; // Coeficiente de fricción inicial
    QPixmap hojaSprites;
    QPixmap sprite;
    int cont=0;
    QSize limites;
    QTimer *timerMov;
    QTimer* friccionTimer; // Temporizador para aplicar la fricción
    QTimer* dificultadTimer; // Temporizador para aumentar la fricción
    int dx, dy;
    QGraphicsView *vista;

private:
    void aplicarFriccion(); // Método para aplicar la fricción
    void aumentarDificultad(); // Método para incrementar la dificultad

public:
    Bart(QGraphicsView *vista);
    void keyPressEvent(QKeyEvent *event) override;
    void extracted();
    void movimiento(int dx, int dy);
    void confSprite(int dir,int dirX);

public slots:
    void movContinuo();

signals:
    void llegarBorde();

};

#endif // BART_H
