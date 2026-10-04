#include "Usuario.h"

Usuario::Usuario(int id, const std::string& nombre) : id(id), nombre(nombre) {}

int Usuario::getId() const {
    return id;
}

std::string Usuario::getNombre() const {
    return nombre;
}

void Usuario::setNombre(const std::string& nuevoNombre) {
    nombre = nuevoNombre;
}
