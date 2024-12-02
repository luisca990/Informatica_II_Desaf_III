#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <limits>

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
        lanzar(15, 45, 0.02);
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
        saltar(5, 2 * M_PI);
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

    virtual void mover(int dx, int dy) {
        posicionX += dx;
        posicionY += dy;
        std::cout << nombre << " se ha movido a (" << posicionX << ", " << posicionY << ").\n";
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
    int puntuacion;

public:
    Nivel(int numero, Bart& jugador) : numeroNivel(numero), bart(jugador), puntuacion(0) {}

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
        std::cout << "Nivel " << numeroNivel << " completado con " << puntuacion << " puntos.\n";
    }

    int getPuntuacion() const { return puntuacion; }

private:
    void nivel1() {
        bart.interactuarCon("teléfono");
        puntuacion += 50;
        std::cout << "Evita que Marge te atrape moviéndote:\n";
        for (int i = 0; i < 3; ++i) {
            int dx, dy;
            std::cout << "Ingresa movimiento (X, Y): ";
            
            // Mejora en la entrada de datos para evitar errores de entrada
            while (!(std::cin >> dx >> dy)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada inválida. Ingresa movimiento (X, Y): ";
            }
            
            bart.mover(dx, dy);
            puntuacion += 10;
        }
    }

    void nivel2() {
        bart.interactuarCon("aeropuerto");
        puntuacion += 75;
        bart.agregarObjeto(std::make_unique<Boomerang>());
        std::cout << "Bart escapó de los guardias.\n";
        puntuacion += 25;
    }

    void nivel3() {
        std::cout << "¡Escapa de la gran bota!\n";
        for (int i = 0; i < 5; ++i) {
            int dx, dy;
            std::cout << "Ingresa movimiento para evadir (X, Y): ";
            
            // Mejora en la entrada de datos para evitar errores de entrada
            while (!(std::cin >> dx >> dy)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada inválida. Ingresa movimiento para evadir (X, Y): ";
            }
            
            bart.mover(dx, dy);
            puntuacion += 20;
        }
    }

    void nivel4() {
        std::cout << "Bart corre hacia el consulado...\n";
        puntuacion += 150;
        bart.escapar();
    }
};

// Clase Juego
class Juego {
private:
    Bart bart;
    bool jugando;
    int puntuacionTotal;
    std::vector<int> puntuacionesPorNivel;

public:
    Juego() : bart(), jugando(true), puntuacionTotal(0) {
        bart.agregarObjeto(std::make_unique<Rana>());
    }

    void iniciar() {
        mostrarMenuPrincipal();
    }

private:
    void mostrarMenuPrincipal() {
        while (true) {
            std::cout << "\n--- Menú Principal ---\n";
            std::cout << "1. Jugar nuevo juego\n";
            std::cout << "2. Continuar partida guardada\n";
            std::cout << "3. Salir\n";
            std::cout << "Seleccione una opción: ";
            
            int opcion;
            
            // Mejora en la entrada de datos para evitar errores de entrada
            while (!(std::cin >> opcion)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada inválida. Seleccione una opción: ";
            }

            switch (opcion) {
                case 1:
                    jugarNuevoJuego();
                    break;
                case 2:
                    continuarPartida();
                    break;
                case 3:
                    std::cout << "¡Gracias por jugar!\n";
                    return;
                default:
                    std::cout << "Opción inválida. Intente de nuevo.\n";
            }
        }
    }

    void jugarNuevoJuego() {
        puntuacionTotal = 0;
        puntuacionesPorNivel.clear();
        for (int nivel = 1; nivel <= 4 && jugando; ++nivel) {
            Nivel nivelActual(nivel, bart);
            nivelActual.iniciar();
            puntuacionTotal += nivelActual.getPuntuacion();
            puntuacionesPorNivel.push_back(nivelActual.getPuntuacion());
            guardarProgreso(nivel + 1, puntuacionTotal);
        }
        mostrarEstadisticas();
    }

    void continuarPartida() {
        int nivel = 1, puntuacion = 0;
        if (cargarProgreso(nivel, puntuacion)) {
            puntuacionTotal = puntuacion;
            for (int i = nivel; i <= 4 && jugando; ++i) {
                Nivel nivelActual(i, bart);
                nivelActual.iniciar();
                puntuacionTotal += nivelActual.getPuntuacion();
                puntuacionesPorNivel.push_back(nivelActual.getPuntuacion());
                guardarProgreso(i + 1, puntuacionTotal);
            }
            mostrarEstadisticas();
        } else {
            std::cout << "No se encontró una partida guardada.\n";
        }
    }

    void mostrarEstadisticas() {
        std::cout << "\n--- Estadísticas del Juego ---\n";
        std::cout << "Puntuación Total: " << puntuacionTotal << " puntos\n";
        
        std::cout << "Puntuación por Niveles:\n";
        for (size_t i = 0; i < puntuacionesPorNivel.size(); ++i) {
            std::cout << "Nivel " << (i + 1) << ": " << puntuacionesPorNivel[i] << " puntos\n";
        }
        
        std::cout << "\nInventario final de Bart:\n";
        bart.mostrarInventario();
        
        std::cout << "\n¿Desea guardar su progreso? (1-Sí, 0-No): ";
        
        int guardar;
        // Mejora en la entrada de datos para evitar errores de entrada
        while (!(std::cin >> guardar)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. ¿Desea guardar su progreso? (1-Sí, 0-No): ";
        }
        
        if (guardar == 1) {
            guardarProgreso(puntuacionesPorNivel.size() + 1, puntuacionTotal);
            std::cout << "Progreso guardado exitosamente.\n";
        }
        
        std::cout << "\n¡Juego terminado!\n";
    }

    bool guardarProgreso(int nivel, int puntuacion) {
        std::ofstream archivo("progreso.txt");
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir archivo de progreso para guardar.\n";
            return false;
        }
        
        archivo << nivel << "\n";
        archivo << puntuacion << "\n";
        
        archivo.close();
        return true;
    }

    bool cargarProgreso(int& nivel, int& puntuacion) {
        std::ifstream archivo("progreso.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se encontró archivo de progreso.\n";
            return false;
        }
        
        if (!(archivo >> nivel >> puntuacion)) {
            std::cerr << "Error al leer archivo de progreso.\n";
            archivo.close();
            return false;
        }
        
        archivo.close();
        return true;
    }
};

// Función principal
int main() {
    try {
        Juego juegoDelBart;
        juegoDelBart.iniciar();
    } catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
