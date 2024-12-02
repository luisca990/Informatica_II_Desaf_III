#include "boomerang.h"
#include "GameException.h"
#include <QtMath>
#include <QDebug>

Boomerang::Boomerang(QPointF start, qreal angle, qreal speed, QObject* parent)
    : QObject(parent), QGraphicsPixmapItem(), startPos(start), angle(qDegreesToRadians(angle)),
    speed(speed), time(0), gravity(9.8), returnFactor(0.01),
    currentFrame(0), frameWidth(17), frameHeight(30) { // Asume que cada cuadro mide 45x45

    try {
        // Carga el sprite
        spriteSheet = QPixmap(":/Boomerang.png"); // Cambia esto al path del sprite
    } catch (const GameException& e) {
        qDebug()<< e.what() << "\n";
    }


    setupSprite();

    setPos(startPos); // Posición inicial

    // Configura temporizador para movimiento
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Boomerang::updatePosition);
    timer->start(30); // Actualiza cada 30 ms

    // Configura temporizador para animación de giro
    frameTimer = new QTimer(this);
    connect(frameTimer, &QTimer::timeout, this, &Boomerang::updateFrame);
    frameTimer->start(100); // Cambia el frame cada 100 ms
}

Boomerang::~Boomerang() {
    if (timer) timer->stop();
    if (frameTimer) frameTimer->stop();
    delete timer;
    delete frameTimer;
}

void Boomerang::setupSprite() {
    // Corta la primera subimagen
    setPixmap(spriteSheet.copy(0, 75, frameWidth, frameHeight));
}

void Boomerang::updateFrame() {
    // Cambia al siguiente cuadro del sprite
    currentFrame = (currentFrame + 1) % 15; // Hay 4 cuadros en el sprite
    int xOffset = currentFrame * frameWidth;
    setPixmap(spriteSheet.copy(xOffset, 75, frameWidth, frameHeight));
}

void Boomerang::updatePosition() {
    time += 0.03; // Incrementa el tiempo en cada frame

    // Calcula la nueva posición
    calculatePosition();
}

void Boomerang::calculatePosition() {
    // Movimiento parabólico en x
    qreal vx = speed * qCos(angle);      // Componente de velocidad en x
    qreal x = startPos.x() + vx * time; // Posición en x

    // Movimiento parabólico en y
    qreal vy = speed * qSin(angle);              // Componente de velocidad en y
    qreal y = startPos.y() - (vy * time - 0.5 * gravity * time * time); // Posición en y

    // Factor de regreso
    x -= returnFactor * qPow(time, 2); // Ajusta la posición para regresar

    // Actualiza la posición en pantalla
    setPos(x, y);

    // Verifica si el boomerang regresa al origen
    if (time > 5.0 || x < startPos.x()) { // Detener tras 5 segundos o regreso al inicio
        timer->stop();
        frameTimer->stop();
        delete this;
    }
}
