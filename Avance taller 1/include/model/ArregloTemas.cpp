//
// Created by Ignacio Salomon on 29-09-26.
//

#include "../struct/ArregloTemas.h"

#include "../../include/struct/ArregloTemas.h"
#include <cstdlib>

ArregloTemas::ArregloTemas(int capacidadInicial) {
    capacidad = capacidadInicial;
    tamanio = 0;
    temas = (Tema**) std::malloc(sizeof(Tema*) * capacidad);
}

ArregloTemas::~ArregloTemas() {
    for (int i = 0; i < tamanio; i++) {
        delete temas[i];
    }
    std::free(temas);
}

void ArregloTemas::expandir() {
    capacidad *= 2;
    temas = (Tema**) std::realloc(temas, sizeof(Tema*) * capacidad);
}

void ArregloTemas::agregarAlInicio(Tema* t) {
    if (tamanio == capacidad) expandir();
    for (int i = tamanio; i > 0; i--) {
        temas[i] = temas[i - 1];
    }
    temas[0] = t;
    tamanio++;
}

void ArregloTemas::moverAlInicio(int indice) {
    if (indice <= 0 || indice >= tamanio) return;
    Tema* temp = temas[indice];
    for (int i = indice; i > 0; i--) {
        temas[i] = temas[i - 1];
    }
    temas[0] = temp;
}

void ArregloTemas::eliminarPorIndice(int indice) {
    if (indice < 0 || indice >= tamanio) return;
    delete temas[indice];
    for (int i = indice; i < tamanio - 1; i++) {
        temas[i] = temas[i + 1];
    }
    tamanio--;
}

int ArregloTemas::getTamanio() const { return tamanio; }

Tema& ArregloTemas::obtener(int indice) const { return *temas[indice]; }

Tema* ArregloTemas::buscarPorId(const std::string& id) const {
    for (int i = 0; i < tamanio; i++) {
        if (temas[i]->getId() == id) return temas[i];
    }
    return nullptr;
}
