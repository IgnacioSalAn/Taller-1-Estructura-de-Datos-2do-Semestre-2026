#include "ListaRespuestas.h"
#include <sstream>

ListaRespuestas::ListaRespuestas() : cabeza(nullptr), cantidad(0), siguienteId(1) {}

ListaRespuestas::~ListaRespuestas() {
    liberar();
}

void ListaRespuestas::insertarAlInicio(int id, int idUsuario, const std::string& contenido) {
    Respuesta* nuevo = new Respuesta(id, idUsuario, contenido);
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
    cantidad++;
    if (id >= siguienteId) {
        siguienteId = id + 1;
    }
}

void ListaRespuestas::agregarNueva(int idUsuario, const std::string& contenido) {
    insertarAlInicio(siguienteId, idUsuario, contenido);
}

int ListaRespuestas::getCantidad() const {
    return cantidad;
}

Respuesta* ListaRespuestas::getCabeza() const {
    return cabeza;
}

void ListaRespuestas::eliminarPorUsuario(int idUsuario) {
    Respuesta* actual = cabeza;
    Respuesta* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getIdUsuario() == idUsuario) {
            Respuesta* aEliminar = actual;
            if (anterior == nullptr) {
                cabeza = actual->getSiguiente();
                actual = cabeza;
            } else {
                anterior->setSiguiente(actual->getSiguiente());
                actual = actual->getSiguiente();
            }
            delete aEliminar;
            cantidad--;
        } else {
            anterior = actual;
            actual = actual->getSiguiente();
        }
    }
}

void ListaRespuestas::contarPorUsuario(std::map<int, int>& conteo) const {
    Respuesta* actual = cabeza;
    while (actual != nullptr) {
        conteo[actual->getIdUsuario()]++;
        actual = actual->getSiguiente();
    }
}

std::string ListaRespuestas::aCSV() const {
    std::ostringstream oss;
    Respuesta* actual = cabeza;
    bool primero = true;
    while (actual != nullptr) {
        if (!primero) {
            oss << ",";
        }
        oss << actual->getId() << "_" << actual->getIdUsuario() << "_" << actual->getContenido();
        primero = false;
        actual = actual->getSiguiente();
    }
    return oss.str();
}

void ListaRespuestas::liberar() {
    Respuesta* actual = cabeza;
    while (actual != nullptr) {
        Respuesta* siguienteNodo = actual->getSiguiente();
        delete actual;
        actual = siguienteNodo;
    }
    cabeza = nullptr;
    cantidad = 0;
}
