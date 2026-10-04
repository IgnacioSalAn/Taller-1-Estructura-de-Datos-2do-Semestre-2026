#ifndef ARREGLOUSUARIOS_H
#define ARREGLOUSUARIOS_H

#include "Usuario.h"

/**
 * @brief Arreglo dinamico de punteros a Usuario.
 *
 * Cuando la cantidad de usuarios alcanza la capacidad actual, el arreglo
 * se expande utilizando la funcion nativa "realloc", tal como exige la
 * seccion 3.1 del enunciado. Se lleva un contador de expansiones para
 * el apartado de Estadisticas.
 */
class ArregloUsuarios {
private:
    Usuario** usuarios;
    int capacidad;
    int cantidad;
    int expansiones;

    void expandir();

public:
    explicit ArregloUsuarios(int capacidadInicial = 5);
    ~ArregloUsuarios();

    // No se permite copiar (evita doble liberacion de memoria)
    ArregloUsuarios(const ArregloUsuarios&) = delete;
    ArregloUsuarios& operator=(const ArregloUsuarios&) = delete;

    void agregar(Usuario* usuario);
    Usuario* buscarPorId(int id) const;
    int buscarIndicePorId(int id) const;
    bool eliminarPorId(int id);

    int getCantidad() const;
    int getExpansiones() const;
    Usuario* obtenerEn(int indice) const;
};

#endif // ARREGLOUSUARIOS_H
