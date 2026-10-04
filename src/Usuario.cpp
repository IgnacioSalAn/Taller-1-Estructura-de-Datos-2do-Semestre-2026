#include "Usuario.h"

// Constructor (inicializa los atributos por medio de una lista de inicializacion)
Usuario::Usuario(int id, const std::string& nombre) : id(id), nombre(nombre) {}

int Usuario::getId() const { // Retorna el id guardado en la instancia del usuario
    return id; // Retorna el dato (numero entero/int) asociado al ID del usuario
}

std::string Usuario::getNombre() const { // Retorna el nombre guardado en la instancia del usuario
    return nombre; // Retorna el dato (cadena de texto/string) asociado al nombre del usuario
}

void Usuario::setNombre(const std::string& nuevoNombre) { // Asigna un nuevo nombre al atributo privado "nombre" de la clase Usuario
    nombre = nuevoNombre; // Asigna el valor del parametro al atributo (Asigna el nuevo nombre a los nombres de usuarios)
}
