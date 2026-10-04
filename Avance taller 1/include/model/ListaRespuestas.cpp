//
// Created by Ignacio Salomon on 29-09-26.
//

#include "../struct/ListaRespuestas.h"

#include "../../include/struct/ListaRespuestas.h"
#include <iostream>

ListaRespuestas::ListaRespuestas() : cabeza(nullptr), cantidad(0) {}

ListaRespuestas::~ListaRespuestas() {
    NodoRespuesta* actual = cabeza;
    while (actual != nullptr) {
        NodoRespuesta* sig = actual->siguiente;
        delete actual;
        actual = sig;
    }
}

void ListaRespuestas::insertarAlInicio(const Respuesta& resp) {
    cabeza = new NodoRespuesta(resp, cabeza);
    cantidad++;
}

void ListaRespuestas::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "   (Sin respuestas aún)\n";
        return;
    }
    NodoRespuesta* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "   -> [" << actual->dato.getIdMensaje() << "] Usuario "
                  << actual->dato.getIdUsuario() << ": "
                  << actual->dato.getContenido() << "\n";
        actual = actual->siguiente;
    }
}

int ListaRespuestas::contarPorUsuario(int idUsuario) const {
    int contador = 0;
    NodoRespuesta* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato.getIdUsuario() == idUsuario) {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

void ListaRespuestas::eliminarPorUsuario(int idUsuario) {
    while (cabeza != nullptr && cabeza->dato.getIdUsuario() == idUsuario) {
        NodoRespuesta* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        cantidad--;
    }

    NodoRespuesta* actual = cabeza;
    while (actual != nullptr && actual->siguiente != nullptr) {
        if (actual->siguiente->dato.getIdUsuario() == idUsuario) {
            NodoRespuesta* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            cantidad--;
        } else {
            actual = actual->siguiente;
        }
    }
}

int ListaRespuestas::getCantidad() const { return cantidad; }
NodoRespuesta* ListaRespuestas::getCabeza() const { return cabeza; }
