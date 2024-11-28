#include "Bart.h"
#include "boomerang.h"
#include "marge.h"
#include <QKeyEvent>
#include <QDebug>

Bart::Bart(QGraphicsView *vista): vista(vista)
{
    x=2;
    y=476;
    limites = vista->size();
    setFlag(QGraphicsItem::ItemIsFocusable);
    hojaSprites.load(":/Bart2.png");
    sprite = hojaSprites.copy(spriteX,spriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
    timerMov = new QTimer(this);
    connect(timerMov, &QTimer::timeout, this, [=]() {
        movContinuo();
    });

    // Temporizador para aplicar la fricción
    friccionTimer = new QTimer(this);
    connect(friccionTimer, &QTimer::timeout, this, &Bart::aplicarFriccion);
    friccionTimer->start(50); // Se ejecuta cada 50 ms

    // Temporizador para aumentar la dificultad
    dificultadTimer = new QTimer(this);
    connect(dificultadTimer, &QTimer::timeout, this, &Bart::aumentarDificultad);
    dificultadTimer->start(10000); // Aumenta cada 10 segundos
}

/*void Bart::keyPressEvent(QKeyEvent *event){

    switch(event->key()){
    case Qt::Key_A:
        movimiento(-5,0);
        confSprite(54,8);
        dx=-5;
        dy=0;
        if(timerMov->isActive()){
            timerMov->stop();
        }else{timerMov->start(50);}
        break;
    case Qt::Key_D:
        movimiento(5,0);
        confSprite(54,8);
        if(timerMov->isActive()){
            timerMov->stop();
        }
        break;
    case Qt::Key_W:
        movimiento(0,-5);
        confSprite(160,7);
        if(timerMov->isActive()){
            timerMov->stop();
        }
        break;
    case Qt::Key_S:
        movimiento(0,5);
        confSprite(110,8);
        if(timerMov->isActive()){
            timerMov->stop();
        }
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}*/
void Bart::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_A:
        velocidadX = -5; // Asigna velocidad en X
        confSprite(54, 8); // Actualiza el sprite
        break;
    case Qt::Key_D:
        velocidadX = 5;
        confSprite(54, 8);
        break;
    case Qt::Key_W:
        velocidadY = -5;
        confSprite(160, 7);
        break;
    case Qt::Key_S:
        velocidadY = 5;
        confSprite(110, 8);
        break;
    case Qt::Key_Space: { // Presiona espacio para lanzar el boomerang
        QPointF start = pos();        // Posición inicial de Bart
        qreal angle = 45;             // Ángulo de lanzamiento
        qreal speed = 50;             // Velocidad de lanzamiento
        Boomerang* boomerang = new Boomerang(start, angle, speed, this->vista->scene());
        this->vista->scene()->addItem(boomerang); // Agrega a la escena
        break;
    }
    default:
        QGraphicsItem::keyPressEvent(event);
    }

    for (QGraphicsItem* item : vista->scene()->items()) {
        // Verifica si el item es un objeto de la clase Marge
        if (Marge* marge = dynamic_cast<Marge*>(item)) {
            // Comprueba si hay colisión con el objeto actual
            if (this->collidesWithItem(marge)) {
                qDebug() << "Colisión detectada con Marge!";
                // Aquí puedes añadir la lógica adicional en caso de colisión
            }
        }
    }
}

void Bart::movimiento(int dx, int dy){

    if (x+60>limites.width()){
        //emit llegarBorde();
        x = 1;
    }else if (x<1){
        x = 2;
    }else{x += dx;}
    if (y+60 > limites.height()){
        y = limites.height()-60;
    }else if(y<1){
        y = 2;
    }
    else if (y + dy < 335) { // Agregamos la limitación superior aquí
        y = 335;
    }
    else{y += dy;}
    setPos(x,y);
    qDebug()<< x << y;


    for (QGraphicsItem* item : vista->scene()->items()) {
        // Verifica si el item es un objeto de la clase Marge
        if (Marge* marge = dynamic_cast<Marge*>(item)) {
            // Comprueba si hay colisión con el objeto actual
            if (this->collidesWithItem(marge)) {
                qDebug() << "Colisión detectada con Marge!";
                // Aquí puedes añadir la lógica adicional en caso de colisión
            }
        }
    }
}

void Bart::confSprite(int dir, int dirX){
    spriteY = dir;
    spriteX = (spriteAncho*cont)+dirX;
    sprite = hojaSprites.copy(spriteX,spriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
    cont++;
    if(cont==7){cont=0;}
}

void Bart::movContinuo(){
    x+=dx;
    y+=dy;
    confSprite(54,8);
    setPos(x,y);
}

void Bart::aplicarFriccion() {
    // Reducir velocidad en X
    if (velocidadX > 0) {
        velocidadX -= coefFriccion; // La fricción disminuye la velocidad
        if (velocidadX < 0) velocidadX = 0; // Evitar valores negativos
    } else if (velocidadX < 0) {
        velocidadX += coefFriccion; // La fricción desacelera en dirección negativa
        if (velocidadX > 0) velocidadX = 0;
    }

    // Reducir velocidad en Y
    if (velocidadY > 0) {
        velocidadY -= coefFriccion;
        if (velocidadY < 0) velocidadY = 0;
    } else if (velocidadY < 0) {
        velocidadY += coefFriccion;
        if (velocidadY > 0) velocidadY = 0;
    }

    // Actualizar posición
    x += velocidadX;
    y += velocidadY;

    // Limitar el rango de movimiento dentro de los bordes
    if (x < 2) x = 2;
    if (x > limites.width() - 60) x = limites.width() - 60;
    if (y < 335) y = 335;
    if (y > 526) y = 526;

    setPos(x, y); // Actualiza la posición de Bart
}

void Bart::aumentarDificultad() {
    coefFriccion += 0.005f; // Incrementa la fricción cada 10 segundos
    qDebug() << "Coeficiente de fricción aumentado a:" << coefFriccion;
}
