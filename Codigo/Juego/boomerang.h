#ifndef BOOMERANG_H
#define BOOMERANG_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Boomerang : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Boomerang(QPointF start, qreal angle, qreal speed, QObject* parent = nullptr);
    ~Boomerang();

private slots:
    void updatePosition();
    void updateFrame();

private:
    QTimer* timer;         // Temporizador para actualizar movimiento
    QTimer* frameTimer;    // Temporizador para cambiar el sprite
    QPointF startPos;      // Posición inicial
    qreal angle;           // Ángulo de lanzamiento en radianes
    qreal speed;           // Velocidad inicial
    qreal time;            // Tiempo transcurrido
    qreal gravity;         // Aceleración debido a la gravedad
    qreal returnFactor;    // Factor que fuerza el regreso del boomerang

    QPixmap spriteSheet;   // Sprite completo
    int currentFrame;      // Cuadro actual
    int frameWidth;        // Ancho de cada subimagen
    int frameHeight;       // Altura de cada subimagen

    void calculatePosition(); // Calcula la nueva posición
    void setupSprite();       // Configura el sprite inicial
};

#endif // BOOMERANG_H
