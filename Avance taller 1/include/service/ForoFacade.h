//
// Created by Ignacio Salomon on 29-09-26.
//

#ifndef TALLER_1_EST__DATOS__FOROFACADE_H
#define TALLER_1_EST__DATOS__FOROFACADE_H


#include "../struct/ArregloUsuarios.h"
#include "../struct/ArregloTemas.h"
#include <string>

class ForoFacade {
private:
    ArregloUsuarios usuarios;
    ArregloTemas temas;
    Usuario* usuarioAutenticado;

    std::string generarIdTemaAleatorio();

public:
    ForoFacade();

    void cargarUsuarios();
    void cargarTemas();
    void autenticar();

    void desplegarMenu();
    void revisarTema();
    void eliminarUsuario();
    void publicarTema();
    void mostrarEstadisticas();
    void guardarDatos();
};


#endif //TALLER_1_EST__DATOS__FOROFACADE_H
