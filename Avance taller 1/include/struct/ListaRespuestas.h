//
// Created by Ignacio Salomon on 29-09-26.
//

#ifndef TALLER_1_EST__DATOS__LISTARESPUESTAS_H
#define TALLER_1_EST__DATOS__LISTARESPUESTAS_H


#include "NodoRespuesta.h"

class ListaRespuestas {
private:
    NodoRespuesta* cabeza;
    int cantidad;

public:
    ListaRespuestas();
    ~ListaRespuestas();

    // Inserción LIFO
    void insertarAlInicio(const Respuesta& resp);
    void mostrar() const;
    int contarPorUsuario(int idUsuario) const;
    void eliminarPorUsuario(int idUsuario);

    int getCantidad() const;
    NodoRespuesta* getCabeza() const;
};


#endif //TALLER_1_EST__DATOS__LISTARESPUESTAS_H
