//
// Created by Ignacio Salomon on 27-09-26.
//

#include "Usuario.h"
#include <iostream>

Usuario::Usuario() : id(-1), nombre("") {}

Usuario::Usuario(int id, std::string nombre, std::string contrasena, int rol)
    : id(id), nombre(nombre) {}

int Usuario::getId() const { return id; }
std::string Usuario::getNombre() const { return nombre; }

void Usuario::mostrarInformacion() const {
    std::cout << "ID: " << id << " | Nombre: " << nombre << "\n";
}
