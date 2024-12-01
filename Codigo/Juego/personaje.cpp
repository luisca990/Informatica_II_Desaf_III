#include "personaje.h"

Personaje::Personaje(QGraphicsView* vista, QObject* parent)
    : QObject(parent), vista(vista), vida(100), velocidadX(0), velocidadY(0), coefFriccion(0.02f) {
    // Inicializar posición
    x = 0;
    y = 0;

    // Crear barra de vida
    barraVida = new QGraphicsRectItem(0, 0, 100, 10); // Ancho inicial igual a 100
    barraVida->setBrush(QBrush(Qt::green));
    barraVida->setParentItem(this); // La barra sigue al personaje
    barraVida->setPos(0, -15);      // Posición encima del personaje
}

Personaje::~Personaje() {
    delete barraVida;
}

void Personaje::recibirDanio(int danio,float multiplicadorDano) {
    // Ajustamos el daño recibido con el multiplicador
    int danoFinal = static_cast<int>(danio + (multiplicadorDano)*100); // El daño se incrementa con el tiempo
    qDebug() << "Vida de Bart Inicial: " << vida<< "Daño recibido: " << (multiplicadorDano)*100;
    vida -= danoFinal;
    if (vida <= 0) {
        vida = 0;
        emit gameOver(); // Emitir señal de Game Over
    }
    qDebug() << "Vida de Bart: " << vida << "Daño recibido: " << danoFinal;
    actualizarBarraVida();
}

int Personaje::getVida() const {
    return vida;
}

void Personaje::actualizarBarraVida() {
    int ancho = static_cast<int>(vida); // Escalar ancho según la vida restante
    barraVida->setRect(0, 0, ancho, 10);

    // Cambiar color según la vida
    if (vida > 50) {
        barraVida->setBrush(QBrush(Qt::green));
    } else if (vida > 20) {
        barraVida->setBrush(QBrush(Qt::yellow));
    } else {
        barraVida->setBrush(QBrush(Qt::red));
    }
}
