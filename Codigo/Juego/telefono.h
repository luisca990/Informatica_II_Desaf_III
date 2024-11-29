#ifndef TELEFONO_H
#define TELEFONO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Telefono : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Telefono(QPointF posicionInicial, QObject *parent = nullptr);
    ~Telefono();

private slots:
    void cambiarSprite(); // Cambia el sprite del teléfono

private:
    QPixmap imagen1;
    QPixmap imagen2;
    QPixmap imagen3;
    int spriteActual;
    QTimer* timer;
};

#endif // TELEFONO_H
