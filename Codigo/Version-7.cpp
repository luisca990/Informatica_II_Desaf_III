#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>

// Enumeraciones
enum class TipoObjeto {
    Boomerang,
    Rana,
    Donut,
    CervezaDuff
};

enum class TipoEnemigo {
    Canguro,
    Koala,
    Dingo,
    EmU
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
    std::string getNombre() const { return nombre; }
};

// Implementación de objetos específicos
class Boomerang : public Objeto {
public:
    Boomerang() : Objeto("Boomerang", TipoObjeto::Boomerang, 3) {}

    void usar() override {
        std::cout << "¡Bart lanza el boomerang! ¡Golpea a un enemigo y regresa!\n";
        reducirUsos();
    }

    std::string obtenerInformacion() const override {
        return "Boomerang australiano (Usos restantes: " + std::to_string(usos) + ")";
    }
};

class Rana : public Objeto {
public:
    Rana() : Objeto("Rana", TipoObjeto::Rana, 2) {}

    void usar() override {
        std::cout << "¡La rana distrae a los enemigos con su canto!\n";
        reducirUsos();
    }

    std::string obtenerInformacion() const override {
        return "Rana cantora (Usos restantes: " + std::to_string(usos) + ")";
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
        return "Donut curativo (Usos restantes: " + std::to_string(usos) + ")";
    }
};

// Clase base para enemigos
class Enemigo {
protected:
    std::string nombre;
    TipoEnemigo tipo;
    int vida;
    int dano;

public:
    Enemigo(const std::string& nombre, TipoEnemigo tipo, int vida, int dano)
        : nombre(nombre), tipo(tipo), vida(vida), dano(dano) {}
    virtual ~Enemigo() = default;

    virtual void atacar() = 0;
    virtual void recibirDano(int cantidad) {
        vida -= cantidad;
        std::cout << nombre << " recibió " << cantidad << " de daño!\n";
    }
    bool estaVivo() const { return vida > 0; }
    std::string getNombre() const { return nombre; }
    int getDano() const { return dano; }
};

// Implementación de enemigos específicos
class Canguro : public Enemigo {
public:
    Canguro() : Enemigo("Canguro Boxeador", TipoEnemigo::Canguro, 100, 25) {}

    void atacar() override {
        std::cout << "¡El canguro da un fuerte golpe de boxeo!\n";
    }
};

class Koala : public Enemigo {
public:
    Koala() : Enemigo("Koala Furioso", TipoEnemigo::Koala, 50, 15) {}

    void atacar() override {
        std::cout << "¡El koala lanza hojas de eucalipto!\n";
    }
};

// Clase Bart mejorada
class Bart {
private:
    std::string nombre;
    int posicionX, posicionY;
    int vida;
    int energia;
    std::vector<std::unique_ptr<Objeto>> inventario;
    int puntos;

public:
    Bart() : nombre("Bart Simpson"), posicionX(0), posicionY(0), 
             vida(100), energia(100), puntos(0) {}

    void mover(int dx, int dy) {
        posicionX += dx;
        posicionY += dy;
        energia -= 5;
        std::cout << nombre << " se movió a (" << posicionX << ", " << posicionY 
                 << "). Energía restante: " << energia << "\n";
    }

    void agregarObjeto(std::unique_ptr<Objeto> obj) {
        inventario.push_back(std::move(obj));
    }

    void usarObjeto(size_t index) {
        if (index >= inventario.size()) {
            throw std::out_of_range("Objeto no encontrado en el inventario");
        }
        
        if (inventario[index]->tieneUsos()) {
            inventario[index]->usar();
            if (inventario[index]->getNombre() == "Donut") {
                recuperarEnergia(30);
            }
            if (!inventario[index]->tieneUsos()) {
                inventario.erase(inventario.begin() + index);
            }
        }
    }

    void mostrarEstado() const {
        std::cout << "\n=== Estado de " << nombre << " ===\n"
                 << "Vida: " << vida << "\n"
                 << "Energía: " << energia << "\n"
                 << "Puntos: " << puntos << "\n"
                 << "Posición: (" << posicionX << ", " << posicionY << ")\n";
    }

    void mostrarInventario() const {
        std::cout << "\n=== Inventario de " << nombre << " ===\n";
        if (inventario.empty()) {
            std::cout << "El inventario está vacío.\n";
            return;
        }
        
        for (size_t i = 0; i < inventario.size(); ++i) {
            std::cout << i << ". " << inventario[i]->obtenerInformacion() << "\n";
        }
    }

    void recibirDano(int cantidad) {
        vida -= cantidad;
        if (vida < 0) vida = 0;
        std::cout << nombre << " recibió " << cantidad << " de daño. Vida restante: " << vida << "\n";
    }

    void recuperarEnergia(int cantidad) {
        energia += cantidad;
        if (energia > 100) energia = 100;
        std::cout << nombre << " recuperó " << cantidad << " de energía. Energía actual: " << energia << "\n";
    }

    void ganarPuntos(int cantidad) {
        puntos += cantidad;
        std::cout << "¡" << nombre << " ganó " << cantidad << " puntos! Total: " << puntos << "\n";
    }

    bool estaVivo() const { return vida > 0; }
    bool tieneEnergia() const { return energia > 0; }
    int getPuntos() const { return puntos; }
    int getVida() const { return vida; }
    int getX() const { return posicionX; }
    int getY() const { return posicionY; }
};

// Clase Nivel mejorada
class Nivel {
private:
    int numeroNivel;
    std::vector<std::unique_ptr<Enemigo>> enemigos;
    int objetivoX, objetivoY;
    
    void generarEnemigos() {
        int numEnemigos = 2 + numeroNivel;
        for (int i = 0; i < numEnemigos; ++i) {
            if (i % 2 == 0) {
                enemigos.push_back(std::make_unique<Canguro>());
            } else {
                enemigos.push_back(std::make_unique<Koala>());
            }
        }
    }

public:
    Nivel(int nivel) : numeroNivel(nivel) {
        objetivoX = rand() % (10 * nivel);
        objetivoY = rand() % (10 * nivel);
        generarEnemigos();
    }

    void mostrarInfo() const {
        std::cout << "\n=== Nivel " << numeroNivel << " ===\n"
                 << "Objetivo: Llegar a (" << objetivoX << ", " << objetivoY << ")\n"
                 << "Enemigos presentes: " << enemigos.size() << "\n";
    }

    bool verificarObjetivo(int x, int y) const {
        return x == objetivoX && y == objetivoY;
    }

    void encuentroEnemigo(Bart& bart) {
        if (!enemigos.empty() && (rand() % 100 < 30)) {
            auto& enemigo = enemigos.front();
            std::cout << "\n¡" << enemigo->getNombre() << " apareció!\n";
            enemigo->atacar();
            bart.recibirDano(enemigo->getDano());
            enemigos.erase(enemigos.begin());
        }
    }

    int getNumeroNivel() const { return numeroNivel; }
};

class Juego {
private:
    Bart bart;
    std::vector<Nivel> niveles;
    size_t nivelActual; // Cambiado de int a size_t para coincidir con size_type
    bool juegoTerminado;

    void inicializarNiveles() {
        for (size_t i = 1; i <= 3; ++i) { // Cambiado el tipo de i a size_t
            niveles.emplace_back(i);
        }
    }

    void mostrarMenu() {
        std::cout << "\n=== Menú de Juego ===\n"
                 << "1. Mover a Bart\n"
                 << "2. Usar objeto\n"
                 << "3. Ver inventario\n"
                 << "4. Ver estado\n"
                 << "5. Guardar partida\n"
                 << "6. Cargar partida\n"
                 << "7. Salir\n"
                 << "Elije una opción: ";
    }

    void guardarPartida() {
        std::ofstream archivo("partida.save");
        if (archivo.is_open()) {
            archivo << nivelActual << " " 
                   << bart.getVida() << " "
                   << bart.getPuntos() << "\n";
            std::cout << "Partida guardada con éxito.\n";
        }
    }

    void cargarPartida() {
        std::ifstream archivo("partida.save");
        if (archivo.is_open()) {
            size_t nivel;
            archivo >> nivel;
            if (nivel < niveles.size()) {
                nivelActual = nivel;
            }
            int vida, puntos;
            archivo >> vida >> puntos;
            std::cout << "Partida cargada con éxito.\n";
        }
    }

public:
    Juego() : nivelActual(0), juegoTerminado(false) {
        srand(time(nullptr));
        inicializarNiveles();
        
        // Equipar a Bart con objetos iniciales
        bart.agregarObjeto(std::make_unique<Boomerang>());
        bart.agregarObjeto(std::make_unique<Donut>());
        bart.agregarObjeto(std::make_unique<Rana>());
    }

    void ejecutar() {
        std::cout << "¡Bienvenido a Bart vs. Australia!\n";
        
        while (!juegoTerminado && bart.estaVivo() && nivelActual < niveles.size()) {
            niveles[nivelActual].mostrarInfo();
            
            int opcion;
            mostrarMenu();
            std::cin >> opcion;

            switch (opcion) {
                case 1: {
                    int dx, dy;
                    std::cout << "Ingrese movimiento en X e Y: ";
                    std::cin >> dx >> dy;
                    bart.mover(dx, dy);
                    niveles[nivelActual].encuentroEnemigo(bart);
                    
                    if (niveles[nivelActual].verificarObjetivo(bart.getX(), bart.getY())) {
                        std::cout << "¡Nivel " << niveles[nivelActual].getNumeroNivel() << " completado!\n";
                        bart.ganarPuntos(100 * (static_cast<int>(nivelActual) + 1));
                        nivelActual++;
                    }
                    break;
                }
                case 2: {
                    bart.mostrarInventario();
                    std::cout << "Seleccione objeto a usar: ";
                    size_t index;
                    std::cin >> index;
                    try {
                        bart.usarObjeto(index);
                    } catch (const std::out_of_range&) {
                        std::cout << "Objeto inválido.\n";
                    }
                    break;
                }
                case 3:
                    bart.mostrarInventario();
                    break;
                case 4:
                    bart.mostrarEstado();
                    break;
                case 5:
                    guardarPartida();
                    break;
                case 6:
                    cargarPartida();
                    break;
                case 7:
                    juegoTerminado = true;
                    break;
                default:
                    std::cout << "Opción inválida.\n";
            }

            if (!bart.tieneEnergia()) {
                std::cout << "¡Bart se ha quedado sin energía!\n";
                juegoTerminado = true;
            }
        }

        if (nivelActual >= niveles.size()) {
            std::cout << "\n¡Felicidades! Has completado el juego.\n"
                     << "Puntuación final: " << bart.getPuntos() << "\n";
        } else if (!bart.estaVivo()) {
            std::cout << "\nGame Over - Bart ha sido derrotado.\n";
        }
    }
};

int main() {
    Juego juego;
    juego.ejecutar();
    return 0;
}
