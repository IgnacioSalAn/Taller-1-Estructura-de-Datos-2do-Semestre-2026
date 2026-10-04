#include "Respuesta.h"

Respuesta::Respuesta(int id, int idUsuario, const std::string& contenido)
    : id(id), idUsuario(idUsuario), contenido(contenido), siguiente(nullptr) {}

int Respuesta::getId() const { // Retorna el Id corresponndiente a la instancia del mensaje
    return id; // Retorna el dato (tipo entero/int) asociado al ID de la respuesta al tema
}

int Respuesta::getIdUsuario() const { // Retorna el ID correspondiente al usuario que respondio a un tema
    return idUsuario; // Retorna el dato (tipo entero/int) asociado al ID del usuario que hizo la respuesta
}

std::string Respuesta::getContenido() const { // Retorna el contenido (cadena de texto) de la respuesta
    return contenido; // Retorna el dato (tipo string/string) asociado al contenido de la respuesta
}

Respuesta* Respuesta::getSiguiente() const { // Retorna el puntero al siguiente nodo de la lista
    return siguiente; // Retorna la direccion guardada en 'siguiente'
}

void Respuesta::setSiguiente(Respuesta* nuevoSiguiente) { // Asigna la direccion del nuevo nodo que continuara en la lista enlazada
    siguiente = nuevoSiguiente; // Actualiza el puntero de enlace
}
