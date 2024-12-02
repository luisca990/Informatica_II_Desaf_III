/*#ifndef BART_H
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
*/

#ifndef BART_H
#define BART_H

#include "archivo.h"
#include "personaje.h"
#include <QTimer>
#include <QPixmap>
#include <QObject>

class Bart : public Personaje {
    Q_OBJECT

public:
    Bart(QGraphicsView* vista);

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void aplicarFriccion() override;
    void lanzarBoomerang();
    void confSprite(int dir, int dirX);
    void aumentarDificultad();
    void detectarColisiones();
    void aumentarDano(); // Método para aumentar el daño

signals:
    void llegarBorde(); // Señal que se emite cuando Bart alcanza los bordes
    void victoria();

private:
    Archivo archivo;
    QPixmap hojaSprites;
    QPixmap sprite;
    QSize limites;
    int spriteX;
    int spriteY;
    int spriteAncho;
    int spriteAlto;
    int cont;
    int xSprite;
    int ySprite;
    int danoBase;          // Daño base que Bart recibe
    int cantidadBomerang;
    float multiplicadorDano; // Factor que aumenta con el tiempo
    std::string nombreArchivo;

    QTimer* aumentoDanoTimer; // Temporizador para aumentar el daño
    QTimer* lanzamientoTimer;      // Temporizador para lanzar boomerangs
    QTimer* friccionTimer;
    QTimer* dificultadTimer;
    int delayBetweenBoomerangs;    // Retraso acumulativo entre lanzamientos
};

#endif // BART_H
