#ifndef MARGE_H
#define MARGE_H

#include "enemigo.h"

#include <QLabel>
#include <QTimer>
#include <qgraphicsitem.h>
#include <QRandomGenerator>
class Marge:public QObject,public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Marge(QObject* parent = nullptr);
    void recibirDanio(int danio); // Llamado cuando recibe un golpe del boomerang
    int getVida() const;

private slots:
    void moveLeft();
    void updateFrame();


private:
    int currentFrame;
    int randomStepRange; // Rango de variación aleatoria en el movimiento vertical
    int vida; // Vida de Marge
    int golpesRecibidos; // Contador de golpes del boomerang
    QPixmap sprite;
    QTimer* timer;
    QGraphicsRectItem* barraVida; // Representa la barra de vida
    void actualizarBarraVida(); // Actualiza visualmente la barra de vida

};



#endif // MARGE_H
