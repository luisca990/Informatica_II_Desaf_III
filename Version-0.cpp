#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>

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

// Clase Boomerang
class Boomerang : public Objeto {
public:
    Boomerang() : Objeto("Boomerang", TipoObjeto::Boomerang) {}
    void usar() override {
        std::cout << "Bart lanza el boomerang.\n";
    }
    std::string obtenerInformacion() override {
        return "Un boomerang tradicional australiano.";
    }
};

// Clase Rana
class Rana : public Objeto {
public:
    Rana() : Objeto("Rana", TipoObjeto::Rana) {}
    void usar() override {
        std::cout << "Bart libera la rana.\n";
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
        if (index < inventario.size()) {
            inventario[index]->usar();
        } else {
            std::cout << "Índice fuera de rango.\n";
        }
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

// Clase Juego
class Juego {
private:
    Bart bart;

public:
    void iniciarJuego() {
        std::cout << "Iniciando el juego...\n";
        // Agregar algunos objetos al inventario de Bart
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

            switch (opcion) {
                case 1: {
                    int dx, dy;
                    std::cout << "Ingrese la distancia a mover en X e Y: ";
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
        }
    }
};

int main() {
    Juego juego;
    juego.iniciarJuego();
    juego.mostrarMenu();
    return 0;
}
