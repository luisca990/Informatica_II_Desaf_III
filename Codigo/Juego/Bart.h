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
    int vida; // Vida actual
    int cont=0;
    int dx, dy;
    int delayBetweenBoomerangs; // Retraso acumulativo entre lanzamientos de boomerang
    float velocidadX = 0.0f; // Velocidad horizontal de Bart
    float velocidadY = 0.0f; // Velocidad vertical de Bart
    float coefFriccion = 0.02f; // Coeficiente de fricción inicial
    QPixmap hojaSprites;
    QPixmap sprite;
    QSize limites;
    QTimer *timerMov;
    QTimer* friccionTimer; // Temporizador para aplicar la fricción
    QTimer* dificultadTimer; // Temporizador para aumentar la fricción
    QTimer* lanzamientoTimer; // Temporizador para retraso entre lanzamientos de boomerang
    QGraphicsView *vista;
    QGraphicsRectItem* barraVida; // Representa la barra de vida




private:
    void aplicarFriccion(); // Método para aplicar la fricción
    void aumentarDificultad(); // Método para incrementar la dificultad
    void actualizarBarraVida(); // Actualiza visualmente la barra de vida

public:
    Bart(QGraphicsView *vista);
    void keyPressEvent(QKeyEvent *event) override;
    void extracted();
    void movimiento(int dx, int dy);
    void confSprite(int dir,int dirX);
    void recibirDanio(int danio); // Llamado cuando hay colisión con Marge
    int getVida() const; // Obtener la vida actual
    void lanzarBoomerang();

public slots:
    void movContinuo();

signals:
    void llegarBorde();
    void gameOver(); // Señal para indicar que el juego terminó

};

#endif // BART_H
