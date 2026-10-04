#include "ArregloUsuarios.h"
#include <cstdlib>

ArregloUsuarios::ArregloUsuarios(int capacidadInicial)
    : capacidad(capacidadInicial), cantidad(0), expansiones(0) {
    usuarios = static_cast<Usuario**>(malloc(sizeof(Usuario*) * capacidad));
}

ArregloUsuarios::~ArregloUsuarios() {
    for (int i = 0; i < cantidad; i++) {
        delete usuarios[i];
    }
    free(usuarios);
}

void ArregloUsuarios::expandir() {
    capacidad *= 2;
    Usuario** nuevo = static_cast<Usuario**>(realloc(usuarios, sizeof(Usuario*) * capacidad));
    usuarios = nuevo;
    expansiones++;
}

void ArregloUsuarios::agregar(Usuario* usuario) {
    if (cantidad == capacidad) {
        expandir();
    }
    usuarios[cantidad] = usuario;
    cantidad++;
}

int ArregloUsuarios::buscarIndicePorId(int id) const {
    for (int i = 0; i < cantidad; i++) {
        if (usuarios[i]->getId() == id) {
            return i;
        }
    }
    return -1;
}

Usuario* ArregloUsuarios::buscarPorId(int id) const {
    int indice = buscarIndicePorId(id);
    return (indice == -1) ? nullptr : usuarios[indice];
}

bool ArregloUsuarios::eliminarPorId(int id) {
    int indice = buscarIndicePorId(id);
    if (indice == -1) {
        return false;
    }
    delete usuarios[indice];
    for (int i = indice; i < cantidad - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }
    cantidad--;
    return true;
}

int ArregloUsuarios::getCantidad() const {
    return cantidad;
}

int ArregloUsuarios::getExpansiones() const {
    return expansiones;
}

Usuario* ArregloUsuarios::obtenerEn(int indice) const {
    if (indice < 0 || indice >= cantidad) {
        return nullptr;
    }
    return usuarios[indice];
}
