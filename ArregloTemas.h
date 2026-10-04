#ifndef ARREGLOTEMAS_H
#define ARREGLOTEMAS_H

#include <string>
#include "Tema.h"

/**
 * @brief Arreglo dinamico de punteros a Tema.
 *
 * Los temas nuevos (publicados o comentados) se insertan siempre en la
 * posicion 0, de modo que los mas recientes queden primero (seccion 3.2).
 * Al cargar los temas desde el archivo de entrada se usa agregarAlFinal
 * para respetar el orden original del archivo.
 */
class ArregloTemas {
private: // Atributos privados para el control interno del arreglo
    Tema** temas; // Puntero doble que referencia a un arreglo dinamico de punteros a Tema
    int capacidad; // Capacidad maxima de elementos que soporta el arreglo antes de expandirse
    int cantidad; // Cantidad actual de temas almacenados en el arreglo

    void expandirSiEsNecesario(); // Metodo privado para verificar y redimensionar el arreglo en memoria

public: // Metodos publicos para interactuar con la estructura de datos
    explicit ArregloTemas(int capacidadInicial = 5); // Constructor con capacidad por defecto de 5
    ~ArregloTemas(); // Destructor para liberar la memoria dinamica reservada

    // Deshabilita la copia del arreglo para evitar la doble liberacion accidental de memoria
    ArregloTemas(const ArregloTemas&) = delete; // Se deshabilita la copia
    ArregloTemas& operator=(const ArregloTemas&) = delete; // Evita asignar datos de objeto copiado a uno ya existente/inicializado

    void agregarAlInicio(Tema* tema); // Inserta un nuevo tema en el indice 0 desplazando los demas a la derecha
    void agregarAlFinal(Tema* tema); // Agrega un tema al final (usado al cargar el archivo de entrada)
    void moverAlInicio(int indice); // Mueve un tema existente al indice 0 cuando recibe una nueva respuesta

    Tema* buscarPorId(const std::string& id) const; // Busca un tema dado su Id y retorna su direccion
    int buscarIndicePorId(const std::string& id) const; // Busca un tema y retorna su indice numérico
    bool existeId(const std::string& id) const; // Verifica si un Id de tema ya existe en el arreglo
    bool eliminarEnIndice(int indice); // Elimina el tema ubicado en un indice especifico y reordena el arreglo

    // Getter
    int getCantidad() const; // Retorna la cantidad de temas almacenados
    Tema* obtenerEn(int indice) const; // Retorna el tema ubicado en una posicion especifica
};

#endif // ARREGLOTEMAS_H
