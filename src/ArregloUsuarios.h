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
private: // Atributos privados para el control interno de la memoria
    Usuario** usuarios; // Puntero doble que referencia a un arreglo de punteros a objetos Usuario
    int capacidad; // Capacidad maxima de elementos que soporta el arreglo antes de expandirse
    int cantidad; // Cantidad actual de usuarios almacenados en el arreglo
    int expansiones; // Contador de cuantas veces se ha redimensionado la memoria con realloc

    void expandir(); // Metodo privado para duplicar la capacidad del arreglo en memoria (aumentar el tamanio del arreglo)

public: // Metodos publicos para interactuar con la estructura de datos
    explicit ArregloUsuarios(int capacidadInicial = 5); // Constructor con capacidad por defecto de 5
    ~ArregloUsuarios(); // Destructor para liberar la memoria dinamica solicitada

    // Deshabilita la copia del arreglo para evitar la doble liberacion accidental de memoria
    ArregloUsuarios(const ArregloUsuarios&) = delete; // Se deshabilita la copia
    ArregloUsuarios& operator=(const ArregloUsuarios&) = delete; // Evita asignar datos de objeto copiado a uno ya existente/inicializado

    void agregar(Usuario* usuario); // Agrega un nuevo puntero a usuario al final del arreglo (se dirige hacia el final por aniadir un nuevo dato abajo del anterior)
    Usuario* buscarPorId(int id) const; // Busca un usuario dado su Id y retorna su direccion
    int buscarIndicePorId(int id) const; // Busca un usuario y retorna su indice en el arreglo
    bool eliminarPorId(int id); // Elimina un usuario por Id y reordena el arreglo (usa el Id encontrado y elimina sus datos asociados)

    int getCantidad() const; // Retorna la cantidad de usuarios guardados
    int getExpansiones() const; // Retorna cuantas veces se ha expandido el arreglo dinamicamente
    Usuario* obtenerEn(int indice) const; // Retorna el usuario ubicado en una posicion especifica
};

#endif // ARREGLOUSUARIOS_H
