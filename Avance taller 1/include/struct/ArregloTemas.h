//
// Created by Ignacio Salomon on 29-09-26.
//

#ifndef TALLER_1_EST__DATOS__ARREGLOTEMAS_H
#define TALLER_1_EST__DATOS__ARREGLOTEMAS_H


#include "../model/Tema.h"

class ArregloTemas {
private:
    Tema** temas;
    int capacidad;
    int tamanio;

    void expandir();

public:
    ArregloTemas(int capacidadInicial = 2);
    ~ArregloTemas();

    void agregarAlInicio(Tema* t);
    void moverAlInicio(int indice);
    void eliminarPorIndice(int indice);

    int getTamanio() const;
    Tema& obtener(int indice) const;
    Tema* buscarPorId(const std::string& id) const;
};


#endif //TALLER_1_EST__DATOS__ARREGLOTEMAS_H
