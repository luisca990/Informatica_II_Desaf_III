#include "telefono.h"

Telefono::Telefono(QPointF posicionInicial, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteActual(0)
{
    // Cargar las imágenes
    imagen1 = QPixmap(":/Tel2.png");
    imagen2 = QPixmap(":/Tel2.png");
    imagen3 = QPixmap(":/Tel3.png");

    // Verificar si las imágenes se cargaron correctamente
    if (imagen1.isNull() || imagen2.isNull() || imagen3.isNull()) {
        qCritical() << "Error al cargar las imágenes del teléfono.";
        return;
    }

    // Establecer la primera imagen como el sprite inicial
    setPixmap(imagen1);

    // Posicionar el teléfono en la escena
    setPos(posicionInicial);

    // Configurar el temporizador para cambiar el sprite
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Telefono::cambiarSprite);
    timer->start(500); // Cambiar cada 500 ms
}

Telefono::~Telefono() {
    delete timer;
}

void Telefono::cambiarSprite() {
    // Cambia el sprite del teléfono de forma cíclica
    switch (spriteActual) {
    case 0:
        setPixmap(imagen2);
        spriteActual = 1;
        break;
    case 1:
        setPixmap(imagen3);
        spriteActual = 2;
        break;
    case 2:
        setPixmap(imagen1);
        spriteActual = 0;
        break;
    default:
        break;
    }
}
