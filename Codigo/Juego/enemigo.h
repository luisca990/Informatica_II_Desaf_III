#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Enemigo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Enemigo(QObject* parent = nullptr);
    virtual ~Enemigo();

    // Métodos generales
    void setVelocidad(int velocidad); // Configurar velocidad
    int getVelocidad() const;         // Obtener la velocidad actual

protected:
    // Método para definir movimiento específico (debe ser implementado por subclases)
    virtual void mover() = 0;

private:
    int velocidadMovimiento; // Velocidad general del enemigo

    QTimer* timer; // Temporizador para el movimiento

protected slots:
    void moverAutomaticamente(); // Movimiento genérico controlado por el temporizador
};

#endif // ENEMIGO_H
