#include "GameException.h"

// Constructor que inicializa el mensaje
GameException::GameException(const std::string& msg) : message(msg) {}

// Implementación del método what()
const char* GameException::what() const noexcept {
    return message.c_str();
}
