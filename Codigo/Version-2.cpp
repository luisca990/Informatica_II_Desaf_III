#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <unordered_map>

// Enumeración para tipos de objetos
enum class TipoObjeto {
    Boomerang,
    Rana,
    Otro
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
    virtual std::string obtenerInformacion() = 0;
    virtual void lanzar(double velocidadInicial, double angulo, double resistenciaAire) = 0;
    virtual void saltar(double amplitud, double frecuenciaAngular) = 0;
};

// Clase Boomerang con resistencia del aire en lanzamiento parabólico
class Boomerang : public Objeto {
public:
    Boomerang() : Objeto("Boomerang", TipoObjeto::Boomerang) {}

    void usar() override {
        lanzar(15, 45, 0.02); // Velocidad inicial, ángulo, resistencia del aire
    }

    void lanzar(double velocidadInicial, double angulo, double resistenciaAire) override {
        double tiempo = 0;
        double x = 0, y = 0;
        double gravedad = 9.81;
        double anguloRad = angulo * M_PI / 180;

        std::cout << "Lanzando boomerang con resistencia del aire:\n";
        while (y >= 0) {
            x = velocidadInicial * cos(anguloRad) * tiempo * exp(-resistenciaAire * tiempo);
            y = velocidadInicial * sin(anguloRad) * tiempo * exp(-resistenciaAire * tiempo) - 0.5 * gravedad * tiempo * tiempo;
            std::cout << "Posición (" << x << ", " << y << ")\n";
            tiempo += 0.1;
        }
    }

    std::string obtenerInformacion() override {
        return "Un boomerang con resistencia del aire aplicada.";
    }

    void saltar(double amplitud, double frecuenciaAngular) override {
        // Este objeto no implementa la capacidad de saltar, así que no hace nada
    }
};

// Clase Rana con movimiento oscilatorio simple
class Rana : public Objeto {
public:
    Rana() : Objeto("Rana", TipoObjeto::Rana) {}

    void usar() override {
        saltar(5, 2 * M_PI); // Amplitud y frecuencia de salto
    }

    void saltar(double amplitud, double frecuenciaAngular) override {
        double tiempo = 0;
        double y;

        std::cout << "Rana saltando con movimiento oscilatorio:\n";
        while (tiempo <= 2 * M_PI) {
            y = amplitud * sin(frecuenciaAngular * tiempo);
            std::cout << "Altura de salto: " << y << "\n";
            tiempo += 0.1;
        }
    }

    std::string obtenerInformacion() override {
        return "Una rana con movimiento oscilatorio.";
    }

    void lanzar(double velocidadInicial, double angulo, double resistenciaAire) override {
        // Este objeto no implementa la capacidad de lanzar, así que no hace nada
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

// Clase Bart con inventario de objetos
class Bart : public Personaje {
private:
    std::vector<std::unique_ptr<Objeto>> inventario;
public:
    Bart() : Personaje("Bart", 0, 0, 100) {}

    void agregarObjeto(std::unique_ptr<Objeto> obj) {
        inventario.push_back(std::move(obj));
    }
    void usarObjeto(size_t index) {
        if (index >= inventario.size()) throw std::out_of_range("Índice fuera de rango en inventario");
        inventario[index]->usar();
    }
    void mostrarInventario() {
        if (inventario.empty()) {
            std::cout << "El inventario está vacío.\n";
        } else {
            std::cout << "Inventario de Bart:\n";
            for (size_t i = 0; i < inventario.size(); ++i) {
                std::cout << i << ". " << inventario[i]->obtenerInformacion() << "\n";
            }
        }
    }
    void escapar() override { std::cout << "Bart intenta escapar.\n"; }
    void defender() override { std::cout << "Bart se defiende.\n"; }
};

// Clase Enemigo con movimiento oscilatorio
class Enemigo : public Personaje {
private:
    int nivelAgresividad;
    double amplitud, frecuencia, fase;
public:
    Enemigo(const std::string& nombre, int x, int y, int agresividad)
        : Personaje(nombre, x, y, 100), nivelAgresividad(agresividad), amplitud(5 + agresividad), frecuencia(1.0 + agresividad * 0.1), fase(0.0) {}

    void patrullar() { std::cout << nombre << " patrullando con movimiento oscilatorio.\n"; }
    void moverOscilatorio(double tiempo) {
        posicionX += static_cast<int>(amplitud * sin(frecuencia * tiempo + fase));
        std::cout << nombre << " se movió a (" << posicionX << ", " << posicionY << ").\n";
    }
    void atacar(Bart& bart) {
        std::cout << "El enemigo ataca a Bart.\n";
        bart.recibirDano(nivelAgresividad * 10);
    }
    void escapar() override { std::cout << nombre << " intenta escapar.\n"; }
    void defender() override { std::cout << nombre << " se defiende.\n"; }
};

// Clase Nivel con noción de dificultad y atributos dinámicos
class Nivel {
private:
    int dificultad;
    std::vector<std::unique_ptr<Enemigo>> enemigos;
    std::unordered_map<std::string, double> propiedades;

public:
    Nivel(int dificultad) : dificultad(dificultad) {
        propiedades["gravedad"] = 9.8 + dificultad * 0.5;
        propiedades["velocidadEnemigo"] = 1.0 + dificultad * 0.2;
    }

    void cargarNivel() {
        std::cout << "Cargando nivel con dificultad " << dificultad << ".\n";
        int numEnemigos = dificultad * 2;
        for (int i = 0; i < numEnemigos; ++i) {
            enemigos.push_back(std::make_unique<Enemigo>("Enemigo" + std::to_string(i), 0, 0, dificultad));
        }
    }

    void actualizar() {
        for (auto& enemigo : enemigos) {
            enemigo->moverOscilatorio(propiedades["velocidadEnemigo"]);
            enemigo->patrullar();
            enemigo->atacar(bart);
        }
    }

private:
    Bart bart;
};

// Clase Juego con manejo de dificultad
class Juego {
private:
    std::vector<std::unique_ptr<Nivel>> niveles;
    int puntuacion;

public:
    Juego() : puntuacion(0) {
        niveles.push_back(std::make_unique<Nivel>(1)); // Nivel inicial con dificultad 1
        niveles[0]->cargarNivel();
    }

    void iniciarJuego() {
        std::cout << "Iniciando el juego...\n";
        Bart bart;
        bart.agregarObjeto(std::make_unique<Boomerang>());
        bart.agregarObjeto(std::make_unique<Rana>());
        mostrarMenu(bart);
    }

    void mostrarMenu(Bart& bart) {
        int opcion = 0;
        while (opcion != 6) {
            std::cout << "\n--- Menú de Juego ---\n";
            std::cout << "1. Mover a Bart\n";
            std::cout << "2. Usar un objeto\n";
            std::cout << "3. Mostrar inventario\n";
            std::cout << "4. Escapar\n";
            std::cout << "5. Defender\n";
            std::cout << "6. Salir\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;

            try {
                switch (opcion) {
                    case 1: {
                        int dx, dy;
                        std::cout << "Ingrese la distancia en X e Y: ";
                        std::cin >> dx >> dy;
                        bart.mover(dx, dy);
                        break;
                    }
                    case 2: {
                        bart.mostrarInventario();
                        std::cout << "Seleccione el índice del objeto a usar: ";
                        size_t index;
                        std::cin >> index;
                        bart.usarObjeto(index);
                        break;
                    }
                    case 3:
                        bart.mostrarInventario();
                        break;
                    case 4:
                        bart.escapar();
                        break;
                    case 5:
                        bart.defender();
                        break;
                    case 6:
                        std::cout << "Finalizando el juego...\n";
                        break;
                    default:
                        std::cout << "Opción no válida. Intente de nuevo.\n";
                        break;
                }
            } catch (const std::exception &e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }
};

// Función principal para ejecutar el juego
int main() {
    Juego juego;
    juego.iniciarJuego();
    return 0;
}
