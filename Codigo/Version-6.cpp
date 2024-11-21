#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <unordered_map>
#include <fstream>

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
};

// Clase Boomerang con resistencia del aire en lanzamiento parabólico
class Boomerang : public Objeto {
public:
    Boomerang() : Objeto("Boomerang", TipoObjeto::Boomerang) {}

    void usar() override {
        std::cout << "Usaste el Boomerang. Regresa tras lanzarlo.\n";
    }

    std::string obtenerInformacion() override {
        return "Un boomerang con resistencia del aire aplicada.";
    }
};

// Clase Rana con movimiento oscilatorio simple
class Rana : public Objeto {
public:
    Rana() : Objeto("Rana", TipoObjeto::Rana) {}

    void usar() override {
        std::cout << "La rana saltó a gran altura.\n";
    }

    std::string obtenerInformacion() override {
        return "Una rana con movimiento oscilatorio.";
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
    int obtenerVida() const { return vida; }
};

// Clase Bart con inventario de objetos
class Bart : public Personaje {
private:
    std::vector<std::unique_ptr<Objeto>> inventario;
    int puntos;

public:
    Bart() : Personaje("Bart", 0, 0, 100), puntos(0) {}

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

    void incrementarPuntos(int cantidad) {
        puntos += cantidad;
        std::cout << "Puntos acumulados: " << puntos << "\n";
    }

    int obtenerPuntos() const { return puntos; }
};

// Clase Nivel
class Nivel {
private:
    int dificultad;

public:
    Nivel(int dificultad) : dificultad(dificultad) {}

    void cargarNivel() {
        std::cout << "Cargando nivel con dificultad " << dificultad << ".\n";
    }

    void completarNivel(Bart& bart) {
        bart.incrementarPuntos(100 * dificultad);
        std::cout << "¡Nivel completado!\n";
    }
};

// Clase Logros
class Logros {
private:
    std::vector<std::string> logros;

public:
    void agregarLogro(const std::string& logro) {
        logros.push_back(logro);
        std::cout << "¡Logro desbloqueado: " << logro << "!\n";
    }

    void mostrarLogros() const {
        if (logros.empty()) {
            std::cout << "No tienes logros aún.\n";
        } else {
            std::cout << "--- Logros Desbloqueados ---\n";
            for (const auto& logro : logros) {
                std::cout << "- " << logro << "\n";
            }
        }
    }
};

// Clase Juego
class Juego {
private:
    Bart bart;
    Nivel nivel;
    Logros logros;
    bool progresoGuardado;

public:
    Juego() : nivel(1), progresoGuardado(false) {
        bart.agregarObjeto(std::make_unique<Boomerang>());
        bart.agregarObjeto(std::make_unique<Rana>());
        nivel.cargarNivel();
    }

    void guardarProgreso() {
        std::ofstream archivo("progreso.txt");
        if (archivo.is_open()) {
            archivo << bart.obtenerPuntos() << "\n";
            archivo << bart.obtenerVida() << "\n";
            progresoGuardado = true;
            std::cout << "Progreso guardado exitosamente.\n";
        }
        archivo.close();
    }

    void cargarProgreso() {
        std::ifstream archivo("progreso.txt");
        if (archivo.is_open()) {
            int puntos, vida;
            archivo >> puntos >> vida;
            bart.incrementarPuntos(puntos - bart.obtenerPuntos()); // Ajustar puntos
            std::cout << "Progreso cargado exitosamente. Vida: " << vida << ", Puntos: " << puntos << ".\n";
            progresoGuardado = true;
        } else {
            std::cout << "No se encontró un progreso guardado.\n";
        }
    }

    void mostrarMenu() {
        int opcion = 0;
        bool jugando = true;

        while (jugando) {
            std::cout << "\n--- Menú Principal ---\n";
            std::cout << "1. Mover a Bart\n";
            std::cout << "2. Usar un objeto\n";
            std::cout << "3. Mostrar inventario\n";
            std::cout << "4. Completar nivel actual\n";
            std::cout << "5. Mostrar logros\n";
            std::cout << "6. Guardar progreso\n";
            std::cout << "7. Cargar progreso\n";
            std::cout << "8. Salir del juego\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1: {
                    int dx, dy;
                    std::cout << "Ingrese movimiento en X e Y: ";
                    std::cin >> dx >> dy;
                    bart.mover(dx, dy);
                    break;
                }
                case 2: {
                    bart.mostrarInventario();
                    size_t index;
                    std::cout << "Seleccione el índice del objeto para usar: ";
                    std::cin >> index;
                    try {
                        bart.usarObjeto(index);
                    } catch (const std::out_of_range&) {
                        std::cout << "Índice inválido.\n";
                    }
                    break;
                }
                case 3:
                    bart.mostrarInventario();
                    break;
                case 4:
                    nivel.completarNivel(bart);
                    logros.agregarLogro("Nivel completado");
                    break;
                case 5:
                    logros.mostrarLogros();
                    break;
                case 6:
                    guardarProgreso();
                    break;
                case 7:
                    cargarProgreso();
                    break;
                case 8:
                    std::cout << "Saliendo del juego...\n";
                    jugando = false;
                    break;
                default:
                    std::cout << "Opción inválida. Inténtelo de nuevo.\n";
            }
        }
    }
};

int main() {
    Juego juego;
    juego.mostrarMenu();
    return 0;
}
