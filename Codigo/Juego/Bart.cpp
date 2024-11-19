#include "Bart.h"
#include <QKeyEvent>
#include <QDebug>

Jugador::Jugador(QGraphicsView *vista): vista(vista)
{
    x=200;
    y=200;
    limites = vista->size();
    setFlag(QGraphicsItem::ItemIsFocusable);
    hojaSprites.load(":/Bart2.png");
    sprite = hojaSprites.copy(spriteX,spriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
    timerMov = new QTimer(this);
    connect(timerMov, &QTimer::timeout, this, [=]() {
        movContinuo();
    });
}

void Jugador::keyPressEvent(QKeyEvent *event){

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
}

void Jugador::movimiento(int dx, int dy){

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
    }else{y += dy;}
    setPos(x,y);
    qDebug()<< x << y;


    for (QGraphicsItem *item : vista->scene()->items()) {
        if (QGraphicsRectItem *rect = dynamic_cast<QGraphicsRectItem*>(item)) {
            if (this->collidesWithItem(rect)) {
                qDebug() << "Colisión detectada con un rectángulo!";
            }
        }
    }
}

void Jugador::confSprite(int dir, int dirX){
    spriteY = dir;
    spriteX = (spriteAncho*cont)+dirX;
    sprite = hojaSprites.copy(spriteX,spriteY,spriteAncho,spriteAlto);
    setPixmap(sprite);
    cont++;
    if(cont==7){cont=0;}
}

void Jugador::movContinuo(){
    x+=dx;
    y+=dy;
    confSprite(54,8);
    setPos(x,y);
}
