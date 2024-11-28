#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>

// Enumeraciones
enum class TipoObjeto {
    Boomerang,
    Rana,
    Donut,
    Escudo
};

// Clase base para objetos
class Objeto {
protected:
    std::string nombre;
    TipoObjeto tipo;
    int usos;

public:
    Objeto(const std::string& nombre, TipoObjeto tipo, int usos = 1)
        : nombre(nombre), tipo(tipo), usos(usos) {}
    virtual ~Objeto() = default;

    virtual void usar() = 0;
    virtual std::string obtenerInformacion() const = 0;

    bool tieneUsos() const { return usos > 0; }
    void reducirUsos() { if (usos > 0) usos--; }
};

// Implementación de objetos
class Boomerang : public Objeto {
public:
    Boomerang() : Objeto("Boomerang", TipoObjeto::Boomerang, 3) {}

    void usar() override {
        std::cout << "¡Bart lanza el boomerang y golpea a un enemigo!\n";
        reducirUsos();
    }

    std::string obtenerInformacion() const override {
        return "Boomerang (Usos restantes: " + std::to_string(usos) + ")";
    }
};

class Rana : public Objeto {
public:
    Rana() : Objeto("Rana", TipoObjeto::Rana, 2) {}

    void usar() override {
        std::cout << "¡Bart libera la rana para distraer a los enemigos!\n";
        reducirUsos();
    }

    std::string obtenerInformacion() const override {
        return "Rana (Usos restantes: " + std::to_string(usos) + ")";
    }
};

class Donut : public Objeto {
public:
    Donut() : Objeto("Donut", TipoObjeto::Donut, 1) {}

    void usar() override {
        std::cout << "¡Bart come un donut y recupera energía!\n";
        reducirUsos();
    }

    std::string obtenerInformacion() const override {
        return "Donut (Usos restantes: " + std::to_string(usos) + ")";
    }
};

class Escudo : public Objeto {
public:
    Escudo() : Objeto("Escudo Protector", TipoObjeto::Escudo, 1) {}

    void usar() override {
        std::cout << "¡Bart usa un escudo para bloquear el próximo ataque!\n";
        reducirUsos();
    }

    std::string obtenerInformacion() const override {
        return "Escudo protector (Usos restantes: " + std::to_string(usos) + ")";
    }
};

// Clase Bart
class Bart {
private:
    int posicionX, posicionY;
    int vida;
    int energia;
    int escudoActivo;
    std::vector<std::unique_ptr<Objeto>> inventario;

public:
    Bart() : posicionX(0), posicionY(0), vida(100), energia(100), escudoActivo(0) {}

    void mover(int dx, int dy) {
        int distancia = std::abs(dx) + std::abs(dy);
        energia -= distancia * 5;
        posicionX += dx;
        posicionY += dy;
        std::cout << "Bart se movió a una nueva ubicación. Energía restante: " << energia << "\n";
    }

    void agregarObjeto(std::unique_ptr<Objeto> obj) {
        inventario.push_back(std::move(obj));
    }

    void usarObjeto(size_t index) {
        if (index >= inventario.size()) {
            std::cout << "Índice inválido. Selecciona un objeto existente.\n";
            return;
        }

        inventario[index]->usar();
        if (inventario[index]->obtenerInformacion().find("Escudo") != std::string::npos) {
            escudoActivo++;
        }
        if (!inventario[index]->tieneUsos()) {
            inventario.erase(inventario.begin() + index);
        }
    }

    void mostrarInventario() const {
        std::cout << "\n=== Inventario ===\n";
        if (inventario.empty()) {
            std::cout << "El inventario está vacío.\n";
            return;
        }
        for (size_t i = 0; i < inventario.size(); ++i) {
            std::cout << i << ". " << inventario[i]->obtenerInformacion() << "\n";
        }
    }

    void recibirDano(int cantidad) {
        if (escudoActivo > 0) {
            std::cout << "¡El escudo bloqueó el ataque!\n";
            escudoActivo--;
        } else {
            vida -= cantidad;
            if (vida < 0) vida = 0;
            std::cout << "Bart recibió " << cantidad << " de daño. Vida restante: " << vida << "\n";
        }
    }

    void recuperarEnergia(int cantidad) {
        energia += cantidad;
        if (energia > 100) energia = 100;
        std::cout << "Bart recuperó " << cantidad << " de energía. Energía actual: " << energia << "\n";
    }

    bool estaVivo() const { return vida > 0; }
    int getX() const { return posicionX; }
    int getY() const { return posicionY; }
    int getVida() const { return vida; }
    int getEnergia() const { return energia; }

    void guardar(std::ofstream &archivo) const {
        archivo << posicionX << " " << posicionY << " " << vida << " " << energia << " " << escudoActivo << " " << inventario.size() << "\n";
        for (const auto& obj : inventario) {
            archivo << static_cast<int>(obj->obtenerInformacion().find("Boomerang") != std::string::npos) << " "
                    << static_cast<int>(obj->obtenerInformacion().find("Rana") != std::string::npos) << " "
                    << static_cast<int>(obj->obtenerInformacion().find("Donut") != std::string::npos) << " "
                    << static_cast<int>(obj->obtenerInformacion().find("Escudo") != std::string::npos) << "\n";
        }
    }

    void cargar(std::ifstream &archivo) {
        int tamanioInventario;
        archivo >> posicionX >> posicionY >> vida >> energia >> escudoActivo >> tamanioInventario;
        
        inventario.clear();
        for (int i = 0; i < tamanioInventario; ++i) {
            int boomerang, rana, donut, escudo;
            archivo >> boomerang >> rana >> donut >> escudo;

            if (boomerang) agregarObjeto(std::make_unique<Boomerang>());
            if (rana) agregarObjeto(std::make_unique<Rana>());
            if (donut) agregarObjeto(std::make_unique<Donut>());
            if (escudo) agregarObjeto(std::make_unique<Escudo>());
        }
    }
};

// Clase Nivel
class Nivel {
private:
    int numeroNivel;
    Bart& bart;
    bool completado;

public:
    Nivel(int nivel, Bart& jugador) : numeroNivel(nivel), bart(jugador), completado(false) {}

    void ejecutar() {
        std::cout << "\n=== Nivel " << numeroNivel << " ===\n";
        std::cout << "Bart debe completar la misión del nivel explorando el mapa.\n";

        while (bart.estaVivo() && !completado) {
            std::cout << "\n1. Mover a Bart\n2. Usar objeto\n3. Ver inventario\n4. Guardar y salir\n5. Regresar al menú principal\n";
            int opcion;
            std::cin >> opcion;

            switch (opcion) {
                case 1: {
                    int dx, dy;
                    std::cout << "Ingrese movimiento en X e Y: ";
                    std::cin >> dx >> dy;
                    bart.mover(dx, dy);
                    
                    // Condición de completar nivel (ejemplo)
                    if ((numeroNivel == 1 && bart.getX() >= 10 && bart.getY() >= 10) ||
                        (numeroNivel == 2 && bart.getX() >= 20 && bart.getY() >= 20)) {
                        completado = true;
                        std::cout << "¡Nivel " << numeroNivel << " completado!\n";
                        return;
                    }
                    break;
                }
                case 2:
                    bart.mostrarInventario();
                    std::cout << "Seleccione objeto a usar: ";
                    size_t index;
                    std::cin >> index;
                    bart.usarObjeto(index);
                    break;
                case 3:
                    bart.mostrarInventario();
                    break;
                case 4:
                    std::cout << "Progreso guardado. Regresando al menú principal.\n";
                    return;
                case 5:
                    std::cout << "Saliendo del nivel...\n";
                    return;
                default:
                    std::cout << "Opción inválida.\n";
            }
        }
    }

    bool estaCompletado() const { return completado; }
};

// Clase Juego
class Juego {
private:
    Bart bart;
    std::vector<std::unique_ptr<Nivel>> niveles;
    bool juegoActivo;

    void guardarPartida() {
        std::ofstream archivo("partida.save");
        if (archivo.is_open()) {
            bart.guardar(archivo);
            for (const auto& nivel : niveles) {
                archivo << nivel->estaCompletado() << "\n";
            }
            std::cout << "Partida guardada correctamente.\n";
        } else {
            std::cout << "No se pudo guardar la partida.\n";
        }
    }

    void cargarPartida() {
        std::ifstream archivo("partida.save");
        if (archivo.is_open()) {
            bart.cargar(archivo);
            for (auto& nivel : niveles) {
                bool completado;
                archivo >> completado;
                if (completado) nivel->ejecutar();
            }
            std::cout << "Partida cargada correctamente.\n";
        } else {
            std::cout << "No hay partida guardada disponible.\n";
        }
    }

public:
    Juego() : juegoActivo(true) {
        niveles.push_back(std::make_unique<Nivel>(1, bart));
        niveles.push_back(std::make_unique<Nivel>(2, bart));
    }

    void iniciar() {
        std::srand(std::time(nullptr)); // Seed for random events

        while (juegoActivo) {
            std::cout << "\n=== Menú Principal ===\n";
            std::cout << "1. Comenzar Nuevo Juego\n";
            std::cout << "2. Cargar Partida\n";
            std::cout << "3. Salir\n";
            
            int opcion;
            std::cin >> opcion;

            // Limpiar búfer de entrada
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (opcion) {
                case 1: {
                    // Reiniciar el juego
                    bart = Bart();
                    niveles.clear();
                    niveles.push_back(std::make_unique<Nivel>(1, bart));
                    niveles.push_back(std::make_unique<Nivel>(2, bart));

                    // Agregar objetos iniciales al inventario
                    bart.agregarObjeto(std::make_unique<Boomerang>());
                    bart.agregarObjeto(std::make_unique<Rana>());
                    bart.agregarObjeto(std::make_unique<Donut>());

                    for (auto& nivel : niveles) {
                        nivel->ejecutar();
                        if (!bart.estaVivo()) {
                            std::cout << "Bart ha sido derrotado. Fin del juego.\n";
                            break;
                        }
                    }
                    break;
                }
                case 2:
                    cargarPartida();
                    break;
                case 3:
                    juegoActivo = false;
                    std::cout << "¡Gracias por jugar!\n";
                    break;
                default:
                    std::cout << "Opción inválida.\n";
            }
        }
    }

    void terminar() {
        guardarPartida();
    }
};

// Función principal del juego
int main() {
    try {
        Juego juegoSimpsons;
        juegoSimpsons.iniciar();
        juegoSimpsons.terminar();
    } catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
