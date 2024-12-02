#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
#include <fstream>
#include <string>

// Incluye otros headers necesarios para las clases que se vayan a almacenar

class Archivo {
public:
    // Método para guardar una venta en un archivo
    // Métodos para guardar cada variable
    void guardarVida(int vida, const std::string& nombreArchivo);
    void guardarEnemigosEliminados(int enemigosEliminados, const std::string& nombreArchivo);
    void guardarBoomerangLanzados(int boomerLanzados, const std::string& nombreArchivo);
    void guardarInformacion(int vida, int enemigosEliminados, int boomerLanzados, const std::string& nombreArchivo);


    // Método para guardar un combustible en un archivo
   // void guardarCombustible(const Combustible& combustible, const std::string& nombreArchivo);

    // Método para leer ventas desde un archivo
    void leerInormacion(const std::string nombreArchivo);

    // Método para leer combustibles desde un archivo
    //void leerCombustibles(const std::string& nombreArchivo);
};

#endif // ARCHIVO_H
