#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <qcontainerfwd.h>
#include <qobject.h>
class Personaje
{
private:
    int spriteX = 8;//0;
    int spriteY = 54;
    int vida=100;
public:
    QString nombre;
    Personaje();
};

#endif // PERSONAJE_H
