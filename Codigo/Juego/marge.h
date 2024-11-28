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

private slots:
    void moveLeft();
    void updateFrame();


private:
    int currentFrame;
    QPixmap sprite;
    QTimer* timer;
    int randomStepRange; // Rango de variación aleatoria en el movimiento vertical

};



#endif // MARGE_H
