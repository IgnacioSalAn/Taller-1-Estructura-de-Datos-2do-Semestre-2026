#include "Tema.h"

Tema::Tema(const std::string& id, const std::string& titulo,
           const std::string& contenido, int idUsuario)
    : id(id), titulo(titulo), contenido(contenido), idUsuario(idUsuario) {}

std::string Tema::getId() const {
    return id;
}

std::string Tema::getTitulo() const {
    return titulo;
}

std::string Tema::getContenido() const {
    return contenido;
}

int Tema::getIdUsuario() const {
    return idUsuario;
}

ListaRespuestas& Tema::getRespuestas() {
    return respuestas;
}
