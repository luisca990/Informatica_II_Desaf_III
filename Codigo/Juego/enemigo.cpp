#include "enemigo.h"

Enemigo::Enemigo(QObject* parent)
    : QObject(parent), QGraphicsPixmapItem(), velocidadMovimiento(5) {
    // Configurar el temporizador para el movimiento automático
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemigo::moverAutomaticamente);
    timer->start(100); // Intervalo por defecto
}

Enemigo::~Enemigo() {
    if (timer) {
        timer->stop();
        delete timer;
    }
}

void Enemigo::setVelocidad(int velocidad) {
    velocidadMovimiento = velocidad;
}

int Enemigo::getVelocidad() const {
    return velocidadMovimiento;
}

void Enemigo::moverAutomaticamente() {
    mover(); // Llama al método definido en las subclases
}
