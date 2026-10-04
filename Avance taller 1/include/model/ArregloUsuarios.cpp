//
// Created by Ignacio Salomon on 29-09-26.
//

#include "../struct/ArregloUsuarios.h"

#include "../../include/struct/ArregloUsuarios.h"
#include <cstdlib>

ArregloUsuarios::ArregloUsuarios(int capacidadInicial) {
    capacidad = capacidadInicial;
    tamanio = 0;
    expansiones = 0;
    usuarios = (Usuario**) std::malloc(sizeof(Usuario*) * capacidad);
}

ArregloUsuarios::~ArregloUsuarios() {
    for (int i = 0; i < tamanio; i++) {
        delete usuarios[i];
    }
    std::free(usuarios);
}

void ArregloUsuarios::expandir() {
    capacidad *= 2;
    expansiones++;
    usuarios = (Usuario**) std::realloc(usuarios, sizeof(Usuario*) * capacidad);
}

void ArregloUsuarios::agregar(const Usuario& u) {
    if (tamanio == capacidad) expandir();
    usuarios[tamanio++] = new Usuario(u);
}

Usuario* ArregloUsuarios::buscarPorId(int id) const {
    for (int i = 0; i < tamanio; i++) {
        if (usuarios[i]->getId() == id) return usuarios[i];
    }
    return nullptr;
}

void ArregloUsuarios::eliminarPorId(int id) {
    for (int i = 0; i < tamanio; i++) {
        if (usuarios[i]->getId() == id) {
            delete usuarios[i];
            for (int j = i; j < tamanio - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            tamanio--;
            break;
        }
    }
}

int ArregloUsuarios::getTamanio() const { return tamanio; }
int ArregloUsuarios::getExpansiones() const { return expansiones; }
Usuario* ArregloUsuarios::obtener(int indice) const {
    if (indice >= 0 && indice < tamanio) return usuarios[indice];
    return nullptr;
}