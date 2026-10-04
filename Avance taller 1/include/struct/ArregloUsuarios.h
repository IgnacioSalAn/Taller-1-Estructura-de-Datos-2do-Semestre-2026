//
// Created by Ignacio Salomon on 29-09-26.
//

#ifndef TALLER_1_EST__DATOS__ARREGLOUSUARIOS_H
#define TALLER_1_EST__DATOS__ARREGLOUSUARIOS_H


#include "../model/Usuario.h"

class ArregloUsuarios {
private:
    Usuario** usuarios;
    int capacidad;
    int tamanio;
    int expansiones;

    void expandir();

public:
    ArregloUsuarios(int capacidadInicial = 2);
    ~ArregloUsuarios();

    void agregar(const Usuario& u);
    Usuario* buscarPorId(int id) const;
    void eliminarPorId(int id);

    int getTamanio() const;
    int getExpansiones() const;
    Usuario* obtener(int indice) const;
};


#endif //TALLER_1_EST__DATOS__ARREGLOUSUARIOS_H
