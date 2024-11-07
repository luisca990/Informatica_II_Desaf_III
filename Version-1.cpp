#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <stdexcept>

// Enumeración para los tipos de objetos
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
};

// Clase Boomerang, que simula un lanzamiento parabólico
class Boomerang : public Objeto {
public:
    Boomerang() : Objeto("Boomerang", TipoObjeto::Boomerang) {}

    void usar() override {
        lanzar(15, 45); // Lanzamiento con velocidad 15 m/s y ángulo de 45 grados
    }

    void lanzar(double velocidadInicial, double angulo) {
        double tiempo = 0;
        double x = 0, y = 0;
        double gravedad = 9.81;
        double anguloRad = angulo * M_PI / 180;

        std::cout << "Lanzando boomerang:\n";
        while (y >= 0) {
            x = velocidadInicial * cos(anguloRad) * tiempo;
            y = velocidadInicial * sin(anguloRad) * tiempo - 0.5 * gravedad * tiempo * tiempo;
            std::cout << "Posición (" << x << ", " << y << ")\n";
            tiempo += 0.1;
        }
    }

    std::string obtenerInformacion() override {
        return "Un boomerang tradicional australiano.";
    }
};

// Clase Rana, que simula un movimiento oscilatorio para sus saltos
class Rana : public Objeto {
public:
    Rana() : Objeto("Rana", TipoObjeto::Rana) {}

    void usar() override {
        saltar(5, 2 * M_PI); // Salto con amplitud de 5 y frecuencia angular 2π
    }

    void saltar(double amplitud, double frecuenciaAngular) {
        double tiempo = 0;
        double y;

        std::cout << "Rana saltando:\n";
        while (tiempo <= 2 * M_PI) {
            y = amplitud * sin(frecuenciaAngular * tiempo);
            std::cout << "Altura de salto: " << y << "\n";
            tiempo += 0.1;
        }
    }

    std::string obtenerInformacion() override {
        return "Una rana que Bart usa para causar caos.";
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

    // Getter para el nombre del personaje
    std::string getNombre() const {
        return nombre;
    }

    virtual void mover(int dx, int dy) {
        posicionX += dx;
        posicionY += dy;
        std::cout << nombre << " se ha movido a la posición (" << posicionX << ", " << posicionY << ").\n";
    }

    virtual void recibirDano(int cantidad) {
        vida -= cantidad;
        if (vida < 0) vida = 0;
        std::cout << nombre << " ha recibido " << cantidad << " de daño. Vida restante: " << vida << ".\n";
    }
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
        if (index >= inventario.size()) {
            throw std::out_of_range("Índice fuera de rango en inventario");
        }
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

    void escapar() {
        std::cout << "Bart intenta escapar.\n";
    }

    void defender() {
        std::cout << "Bart se defiende.\n";
    }
};

// Clase Enemigo
class Enemigo : public Personaje {
private:
    int nivelAgresividad;

public:
    Enemigo(const std::string& nombre, int x, int y, int agresividad)
        : Personaje(nombre, x, y, 100), nivelAgresividad(agresividad) {}

    void atacar(Bart& bart) {
        std::cout << "El enemigo ataca a Bart.\n";
        bart.recibirDano(nivelAgresividad * 10);
    }

    void patrullar() {
        std::cout << nombre << " está patrullando la zona.\n";
    }

    void perseguir(Personaje &objetivo) {
        std::cout << nombre << " está persiguiendo a " << objetivo.getNombre() << ".\n";
    }
};

// Clase Entorno, que aplica fricción en el movimiento
class Entorno {
private:
    double coeficienteFriccion;

public:
    Entorno(double friccion) : coeficienteFriccion(friccion) {}

    void aplicarFriccion(double &dx, double &dy) {
        dx *= (1 - coeficienteFriccion);
        dy *= (1 - coeficienteFriccion);
        std::cout << "Fricción aplicada. Nueva velocidad (" << dx << ", " << dy << ")\n";
    }
};

// Clase Nivel
class Nivel {
private:
    int dificultad;
    std::vector<Enemigo> enemigos;
    std::vector<std::unique_ptr<Objeto>> objetos;

public:
    Nivel(int dificultad) : dificultad(dificultad) {}

    void cargarNivel() {
        std::cout << "Cargando nivel con dificultad " << dificultad << ".\n";
    }

    void agregarEnemigo(const Enemigo& enemigo) {
        enemigos.push_back(enemigo);
    }

    void agregarObjeto(std::unique_ptr<Objeto> obj) {
        objetos.push_back(std::move(obj));
    }

    void actualizar() {
        std::cout << "Actualizando el nivel.\n";
        for (auto& enemigo : enemigos) {
            enemigo.patrullar();
        }
    }
};

// Clase Juego
class Juego {
private:
    Bart bart;
    std::vector<Nivel> niveles;
    int puntuacion;

public:
    Juego() : puntuacion(0) {
        niveles.emplace_back(1); // Agregar un nivel de dificultad 1
        niveles[0].agregarObjeto(std::make_unique<Boomerang>());
        niveles[0].agregarObjeto(std::make_unique<Rana>());
    }

    void iniciarJuego() {
        std::cout << "Iniciando el juego...\n";
        bart.agregarObjeto(std::make_unique<Boomerang>());
        bart.agregarObjeto(std::make_unique<Rana>());
    }

    void mostrarMenu() {
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
    juego.mostrarMenu();
    return 0;
}
