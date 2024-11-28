#ifndef ENEMIGO_H
#define ENEMIGO_H

class Enemigo
{

private:
    int nivelAgresividad;
public:
    void atacarBart();
    void patrullar();
    void reaccionar();
    Enemigo();
};

#endif // ENEMIGO_H
