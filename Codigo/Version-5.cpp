#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <ctime>

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

class Boomerang : public Objeto {
public:
    Boomerang() : Objeto("Boomerang", TipoObjeto::Boomerang) {}

    void usar() override {
        std::cout << "Lanzando boomerang con precisión...\n";
    }

    std::string obtenerInformacion() override {
        return "Un boomerang útil en combate.";
    }
};

class Rana : public Objeto {
public:
    Rana() : Objeto("Rana", TipoObjeto::Rana) {}

    void usar() override {
        std::cout << "Rana saltando con estilo...\n";
    }

    std::string obtenerInformacion() override {
        return "Una rana con habilidades saltarinas.";
    }
};

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
    virtual void recibirDano(int cantidad) {
        vida -= cantidad;
        if (vida < 0) vida = 0;
        std::cout << nombre << " ha recibido " << cantidad << " de daño. Vida restante: " << vida << ".\n";
    }
};

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
};

class Enemigo : public Personaje {
public:
    Enemigo(const std::string& nombre, int x, int y, int vida)
        : Personaje(nombre, x, y, vida) {}

    void atacar(Bart& bart) {
        std::cout << nombre << " ataca a Bart.\n";
        bart.recibirDano(10);
    }
};

class Nivel {
private:
    int dificultad;
    std::vector<Enemigo> enemigos;
public:
    Nivel(int dificultad) : dificultad(dificultad) {}

    void cargarNivel() {
        std::cout << "Cargando nivel con dificultad " << dificultad << ".\n";
        for (int i = 0; i < dificultad; ++i) {
            enemigos.emplace_back("Enemigo" + std::to_string(i), 0, 0, 50);
        }
    }

    void actualizar(Bart& bart) {
        for (auto& enemigo : enemigos) {
            enemigo.atacar(bart);
        }
    }
};

class Juego {
private:
    Bart bart;
    Nivel nivel;
public:
    Juego() : nivel(1) {
        bart.agregarObjeto(std::make_unique<Boomerang>());
        bart.agregarObjeto(std::make_unique<Rana>());
        nivel.cargarNivel();
    }

    void iniciarJuego() {
        std::cout << "Iniciando el juego...\n";
        mostrarMenu();
    }

    void mostrarMenu() {
        int opcion = 0;
        bool jugando = true;

        while (jugando) {
            std::cout << "\n--- Menú Principal ---\n";
            std::cout << "1. Mostrar inventario\n";
            std::cout << "2. Usar un objeto\n";
            std::cout << "3. Siguiente turno\n";
            std::cout << "4. Salir del juego\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1:
                    bart.mostrarInventario();
                    break;
                case 2: {
                    size_t index;
                    bart.mostrarInventario();
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
                    nivel.actualizar(bart);
                    break;
                case 4:
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
    srand(static_cast<unsigned>(time(0)));
    Juego juego;
    juego.iniciarJuego();
    return 0;
}
