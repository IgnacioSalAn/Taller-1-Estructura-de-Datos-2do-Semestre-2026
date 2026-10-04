#include "Respuesta.h"

Respuesta::Respuesta(int id, int idUsuario, const std::string& contenido)
    : id(id), idUsuario(idUsuario), contenido(contenido), siguiente(nullptr) {}

int Respuesta::getId() const {
    return id;
}

int Respuesta::getIdUsuario() const {
    return idUsuario;
}

std::string Respuesta::getContenido() const {
    return contenido;
}

Respuesta* Respuesta::getSiguiente() const {
    return siguiente;
}

void Respuesta::setSiguiente(Respuesta* nuevoSiguiente) {
    siguiente = nuevoSiguiente;
}
