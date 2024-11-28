#include "marge.h"
#include <qevent.h>
#include <qtimer.h>

Marge::Marge(QObject* parent): QObject(parent), QGraphicsPixmapItem() {
    sprite = QPixmap(":/Marge.png"); // Carga el sprite completo

    // Dimensiones de cada cuadro en el sprite
    int frameWidth = 45;   // Ancho de cada cuadro
    int frameHeight = 85;  // Altura de cada cuadro

    currentFrame = 0; // Inicia en el primer cuadro de la fila

    // Configura el QLabel para mostrar la primera subimagen de la tercera fila
    setPixmap(sprite.copy(currentFrame * frameWidth, 175, frameWidth, frameHeight));
    //setScaledContents(true);
    //resize(frameWidth, frameHeight); // Ajusta el QLabel al tamaño del cuadro

    timer = new QTimer(this);

    // Conecta el temporizador para animación y movimiento
    connect(timer, &QTimer::timeout, this, &Marge::updateFrame);
    connect(timer, &QTimer::timeout, this, &Marge::moveLeft);
    timer->start(100); // Controla la velocidad de la animación (100 ms por cuadro)
}

/*void Marge::moveLeft() {
    // Mueve el objeto hacia la izquierda
    int newX = x() - 5; // Nuevo valor en x, decrementando 5 píxeles por movimiento

    // Verificar si el objeto ha salido completamente de los límites
    if (newX < 30) {
        timer->stop(); // Detener el temporizador
        delete this;   // Elimina el objeto
        return;
    }else{
        setPos(newX, y());
    }

    // Actualiza la posición del objeto, manteniendo la posición Y fija

}*/
void Marge::moveLeft() {
    // Mueve el objeto hacia la izquierda
    int newX = x() - 5; // Decrementa la posición en x

    // Genera un desplazamiento aleatorio en y
    int randomStep = QRandomGenerator::global()->bounded(-10, 11); // Movimiento aleatorio entre [-10, 10]
    int newY = y() + randomStep;

    // Verifica límites para evitar que salga del rango visible
    if (newY < 335) { // Límite superior
        newY = 335 + QRandomGenerator::global()->bounded(0, 11); // Rebote hacia abajo
    } else if (newY > 526) { // Límite inferior
        newY = 526 - QRandomGenerator::global()->bounded(0, 11); // Rebote hacia arriba
    }

    // Verifica si el objeto ha salido completamente de los límites horizontales
    if (newX < 30) { // Límite izquierdo
        timer->stop(); // Detener el temporizador
        delete this;   // Elimina el objeto
        return;
    }

    // Mueve a la nueva posición calculada
    setPos(newX, newY);

    // Incrementa la dificultad aumentando el rango de movimiento aleatorio
    if (randomStepRange < 50) { // Límite máximo del rango de variación
        randomStepRange += 1; // Aumenta la dificultad progresivamente
    }
}


void Marge::updateFrame() {
    int frameWidth = 45;   // Ancho de cada cuadro
    int frameHeight = 85;  // Altura de cada cuadro
    int xAdjustment = 10;  // Ajuste para mover cada cuadro 10 píxeles a la derecha

    // Actualiza al siguiente cuadro en la tercera fila
    currentFrame = (currentFrame + 1) % 3; // Cicla entre 3 cuadros (0, 1, 2)
    int xOffset = currentFrame * frameWidth + xAdjustment; // Posición horizontal del cuadro ajustada

    // Ajusta el inicio de la tercera fila
    int yOffset = 175; // Coordenada Y para la tercera fila

    // Corta y muestra el cuadro actual
    setPixmap(sprite.copy(xOffset, yOffset, frameWidth, frameHeight));
}
