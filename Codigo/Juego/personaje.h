#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "archivo.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
#include <QKeyEvent>

class Personaje : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Personaje(QGraphicsView* vista, QObject* parent = nullptr);
    virtual ~Personaje();

    virtual void keyPressEvent(QKeyEvent* event) = 0; // Método abstracto para manejo de teclado
    virtual void aplicarFriccion() = 0;               // Método abstracto para aplicar fricción
    void recibirDanio(int danio,float multiplicadorDano);                     // Reduce la vida del personaje
    int getVida() const;                              // Devuelve la vida actual

signals:
    void gameOver();      // Señal que se emite cuando la vida llega a 0

protected:
    Archivo archivo;
    QGraphicsView* vista; // Vista asociada al personaje
    int vida;             // Vida del personaje
    qreal x, y;           // Posición en la escena
    float velocidadX;     // Velocidad en el eje X
    float velocidadY;     // Velocidad en el eje Y
    float coefFriccion;   // Coeficiente de fricción
    std::string nombreArchivo;

    QGraphicsRectItem* barraVida; // Representa visualmente la vida del personaje

    void actualizarBarraVida(); // Actualiza visualmente la barra de vida
};

#endif // PERSONAJE_H
