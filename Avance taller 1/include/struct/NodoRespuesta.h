//
// Created by Ignacio Salomon on 29-09-26.
//

#ifndef TALLER_1_EST__DATOS__NODORESPUESTA_H
#define TALLER_1_EST__DATOS__NODORESPUESTA_H

#include "../model/Respuesta.h"

// Elemento base para la Lista Enlazada Simple (Sección 3.3)
struct NodoRespuesta {
    Respuesta dato;
    NodoRespuesta* siguiente;

    NodoRespuesta(const Respuesta& r, NodoRespuesta* sig = nullptr)
        : dato(r), siguiente(sig) {}
};


#endif //TALLER_1_EST__DATOS__NODORESPUESTA_H
