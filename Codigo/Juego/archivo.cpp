#include "archivo.h"

// Método para guardar la vida en el archivo
void Archivo::guardarVida(int vida, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::app); // Abrir en modo append
    if (archivo.is_open()) {
        archivo << "Vida: " << vida << "\n";
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar la vida.\n";
    }
}

// Método para guardar los enemigos eliminados en el archivo
void Archivo::guardarEnemigosEliminados(int enemigosEliminados, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::app); // Abrir en modo append
    if (archivo.is_open()) {
        archivo << "Enemigos eliminados: " << enemigosEliminados << "\n";
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar los enemigos eliminados.\n";
    }
}

// Método para guardar la cantidad de boomerangs lanzados en el archivo
void Archivo::guardarBoomerangLanzados(int boomerLanzados, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::app); // Abrir en modo append
    if (archivo.is_open()) {
        archivo << "Cantidad de boomerangs lanzados: " << boomerLanzados << "\n";
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar los boomerangs lanzados.\n";
    }
}

// Método principal para guardar toda la información
void Archivo::guardarInformacion(int vida, int enemigosEliminados, int boomerLanzados, const std::string& nombreArchivo) {
    guardarVida(vida, nombreArchivo);
    guardarEnemigosEliminados(enemigosEliminados, nombreArchivo);
    guardarBoomerangLanzados(boomerLanzados, nombreArchivo);

    // Separador para las entradas
    std::ofstream archivo(nombreArchivo, std::ios::app); // Abrir en modo append
    if (archivo.is_open()) {
        archivo << "--------------------------\n";
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar el separador.\n";
    }
}


// Método para leer ventas desde un archivo
void Archivo::leerInormacion(const std::string nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::cout << linea << std::endl;
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para leer las ventas.\n";
    }
}
