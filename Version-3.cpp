#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <stdexcept>

// Enumeración para tipos de objetos
enum class TipoObjeto {
    Boomerang,
    Rana
};

// Clase abstracta Objeto
class Objeto {
protected:
    std::string nombre;
    TipoObjeto tipo;

public:
    Objeto(const std::string& nombre, TipoObjeto tipo) : nombre(nombre), tipo(tipo) {}
    virtual ~Objeto() = default;

    virtual void usar() = 0;
    virtual std::string obtenerInformacion() const = 0;
};

// Clase Boomerang
class Boomerang : public Objeto {
public:
    Boomerang() : Objeto("Boomerang", TipoObjeto::Boomerang) {}

    void usar() override {
        lanzar(15, 45, 0.02); // Velocidad inicial, ángulo, resistencia del aire
    }

    std::string obtenerInformacion() const override {
        return "Boomerang con resistencia al aire.";
    }

private:
    void lanzar(double velocidadInicial, double angulo, double resistenciaAire) {
        double tiempo = 0;
        double x = 0, y = 0;
        double gravedad = 9.81;
        double anguloRad = angulo * M_PI / 180;

        std::cout << "Lanzando boomerang:\n";
        while (y >= 0) {
            x = velocidadInicial * cos(anguloRad) * tiempo * exp(-resistenciaAire * tiempo);
            y = velocidadInicial * sin(anguloRad) * tiempo * exp(-resistenciaAire * tiempo) - 0.5 * gravedad * tiempo * tiempo;
            std::cout << "Posición (" << x << ", " << y << ")\n";
            tiempo += 0.1;
        }
    }
};

// Clase Rana
class Rana : public Objeto {
public:
    Rana() : Objeto("Rana", TipoObjeto::Rana) {}

    void usar() override {
        saltar(5, 2 * M_PI); // Amplitud y frecuencia angular
    }

    std::string obtenerInformacion() const override {
        return "Rana que salta con movimiento oscilatorio.";
    }

private:
    void saltar(double amplitud, double frecuenciaAngular) {
        double tiempo = 0;
        double y;

        std::cout << "Rana saltando:\n";
        while (tiempo <= 2 * M_PI) {
            y = amplitud * sin(frecuenciaAngular * tiempo);
            std::cout << "Altura: " << y << "\n";
            tiempo += 0.1;
        }
    }
};

// Clase Personaje
class Personaje {
protected:
    std::string nombre;
    int posicionX, posicionY;
    int vida;

public:
    Personaje(const std::string& nombre, int x, int y, int vida)
        : nombre(nombre), posicionX(x), posicionY(y), vida(vida) {}
    virtual ~Personaje() = default;

    std::string getNombre() const { return nombre; }
    int getVida() const { return vida; }

    virtual void mover(int dx, int dy) {
        posicionX += dx;
        posicionY += dy;
        std::cout << nombre << " se ha movido a (" << posicionX << ", " << posicionY << ").\n";
    }

    virtual void recibirDano(int cantidad) {
        vida -= cantidad;
        if (vida < 0) vida = 0;
        std::cout << nombre << " ha recibido " << cantidad << " de daño. Vida restante: " << vida << ".\n";
    }

    virtual void escapar() = 0;
    virtual void defender() = 0;
};

// Clase Bart
class Bart : public Personaje {
private:
    std::vector<std::unique_ptr<Objeto>> inventario;

public:
    Bart() : Personaje("Bart", 0, 0, 100) {}

    void agregarObjeto(std::unique_ptr<Objeto> obj) {
        inventario.push_back(std::move(obj));
    }

    void usarObjeto(size_t index) {
        if (index >= inventario.size()) throw std::out_of_range("Índice fuera de rango.");
        inventario[index]->usar();
    }

    void mostrarInventario() const {
        if (inventario.empty()) {
            std::cout << "El inventario está vacío.\n";
        } else {
            std::cout << "Inventario de Bart:\n";
            for (size_t i = 0; i < inventario.size(); ++i) {
                std::cout << i << ". " << inventario[i]->obtenerInformacion() << "\n";
            }
        }
    }

    void interactuarCon(const std::string& entorno) {
        std::cout << "Bart está interactuando con " << entorno << ".\n";
    }

    void escapar() override {
        std::cout << "Bart intenta escapar.\n";
    }

    void defender() override {
        std::cout << "Bart se defiende.\n";
    }
};

// Clase Nivel
class Nivel {
private:
    int numeroNivel;
    Bart& bart;

public:
    Nivel(int numero, Bart& jugador) : numeroNivel(numero), bart(jugador) {}

    void iniciar() {
        std::cout << "Iniciando nivel " << numeroNivel << "...\n";

        switch (numeroNivel) {
        case 1:
            nivel1();
            break;
        case 2:
            nivel2();
            break;
        case 3:
            nivel3();
            break;
        case 4:
            nivel4();
            break;
        default:
            std::cout << "Nivel no implementado.\n";
            break;
        }
    }

private:
    void nivel1() {
        std::cout << "Bart decide hacer una broma telefónica...\n";
        bart.interactuarCon("teléfono");
        std::cout << "¡Cuidado! Marge está cerca. Muévete para evitar ser descubierto.\n";

        for (int i = 0; i < 5; ++i) {
            int dx, dy;
            std::cout << "Ingresa movimiento (X, Y): ";
            std::cin >> dx >> dy;
            bart.mover(dx, dy);
        }

        std::cout << "Broma realizada con éxito, ¡nivel completado!\n";
    }

    void nivel2() {
        std::cout << "Bienvenido a Australia. Explora el aeropuerto.\n";
        bart.interactuarCon("aeropuerto");
        bart.agregarObjeto(std::make_unique<Boomerang>());
        bart.mostrarInventario();
        bart.escapar();
    }

    void nivel3() {
        std::cout << "¡Cuidado con la Gran Bota! Evita el castigo.\n";
        for (int i = 0; i < 5; ++i) {
            int dx, dy;
            std::cout << "Esquiva la bota (movimiento X, Y): ";
            std::cin >> dx >> dy;
            bart.mover(dx, dy);
        }
        std::cout << "¡Evitaste el castigo! Nivel completado.\n";
    }

    void nivel4() {
        std::cout << "Llega al consulado antes de que te atrapen.\n";
        bart.escapar();
        std::cout << "¡Bart logró llegar al consulado y tocar la puerta!\n";
    }
};

// Clase Juego
class Juego {
private:
    Bart bart;
    bool jugando;

public:
    Juego() : bart(), jugando(true) {
        bart.agregarObjeto(std::make_unique<Boomerang>());
        bart.agregarObjeto(std::make_unique<Rana>());
    }

    void iniciar() {
        std::cout << "¡Bienvenido al juego de Bart vs. Australia!\n";
        for (int nivel = 1; nivel <= 4 && jugando; ++nivel) {
            Nivel nivelActual(nivel, bart);
            nivelActual.iniciar();
        }
        std::cout << "¡Juego terminado!\n";
    }
};

// Punto de entrada
int main() {
    try {
        Juego juego;
        juego.iniciar();
    } catch (const std::exception& e) {
        std::cerr << "Error fatal: " << e.what() << "\n";
    }
    return 0;
}
