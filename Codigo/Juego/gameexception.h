#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <exception>
#include <string>

// Clase de excepción personalizada para el juego
class GameException : public std::exception {
private:
    std::string message; // Mensaje de error

public:
    // Constructor que acepta un mensaje
    explicit GameException(const std::string& msg);

    // Sobrescribe el método what() para devolver el mensaje de error
    const char* what() const noexcept override;
};

#endif // GAMEEXCEPTION_H
