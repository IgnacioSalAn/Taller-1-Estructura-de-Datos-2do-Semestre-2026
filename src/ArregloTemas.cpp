#include "ArregloTemas.h"
#include <cstdlib>

ArregloTemas::ArregloTemas(int capacidadInicial)
    : capacidad(capacidadInicial), cantidad(0) {
    temas = static_cast<Tema**>(malloc(sizeof(Tema*) * capacidad));
}

ArregloTemas::~ArregloTemas() {
    for (int i = 0; i < cantidad; i++) {
        delete temas[i];
    }
    free(temas);
}

void ArregloTemas::expandirSiEsNecesario() {
    if (cantidad == capacidad) {
        capacidad *= 2;
        temas = static_cast<Tema**>(realloc(temas, sizeof(Tema*) * capacidad));
    }
}

void ArregloTemas::agregarAlInicio(Tema* tema) {
    expandirSiEsNecesario();
    for (int i = cantidad; i > 0; i--) {
        temas[i] = temas[i - 1];
    }
    temas[0] = tema;
    cantidad++;
}

void ArregloTemas::agregarAlFinal(Tema* tema) {
    expandirSiEsNecesario();
    temas[cantidad] = tema;
    cantidad++;
}

void ArregloTemas::moverAlInicio(int indice) {
    if (indice <= 0 || indice >= cantidad) {
        return;
    }
    Tema* tema = temas[indice];
    for (int i = indice; i > 0; i--) {
        temas[i] = temas[i - 1];
    }
    temas[0] = tema;
}

int ArregloTemas::buscarIndicePorId(const std::string& id) const {
    for (int i = 0; i < cantidad; i++) {
        if (temas[i]->getId() == id) {
            return i;
        }
    }
    return -1;
}

Tema* ArregloTemas::buscarPorId(const std::string& id) const {
    int indice = buscarIndicePorId(id);
    return (indice == -1) ? nullptr : temas[indice];
}

bool ArregloTemas::existeId(const std::string& id) const {
    return buscarIndicePorId(id) != -1;
}

bool ArregloTemas::eliminarEnIndice(int indice) {
    if (indice < 0 || indice >= cantidad) {
        return false;
    }
    delete temas[indice];
    for (int i = indice; i < cantidad - 1; i++) {
        temas[i] = temas[i + 1];
    }
    cantidad--;
    return true;
}

int ArregloTemas::getCantidad() const {
    return cantidad;
}

Tema* ArregloTemas::obtenerEn(int indice) const {
    if (indice < 0 || indice >= cantidad) {
        return nullptr;
    }
    return temas[indice];
}
