#ifndef LISTARESPUESTAS_H
#define LISTARESPUESTAS_H

#include <string>
#include <map>
#include "Respuesta.h"

/**
 * @brief Lista enlazada simple que almacena las respuestas de un tema.
 *
 * Cada nueva respuesta se agrega siempre al inicio de la lista (cabeza),
 * tal como lo exige el enunciado (seccion 3.3). Al cargar respuestas ya
 * existentes desde el archivo, se insertan en orden inverso para que el
 * recorrido final (cabeza -> cola) respete el orden original del archivo.
 */
class ListaRespuestas {
private: // Metodos privados (solo se pueden modificar desde dentro de la clase)
    Respuesta* cabeza; // Puntero al primer nodo de la lista enlazada (cabeza)
    int cantidad; // Almacena el total de nodos (respuestas) activos en la lista
    int siguienteId; // Lleva registro del proximo ID correlativo a asignar a una nueva respuesta

public:  // Metodos publicos (accesibles desde cualquier parte del programa)
    ListaRespuestas(); // Constructor por defecto que inicializa la lista vacia
    ~ListaRespuestas(); // Destructor para recorrer y liberar nodo por nodo la memoria dinamica

    // Deshabilita la copia para evitar fugas de memoria o punteros colgados (double free) / Niega la copia (evita doble liberacion de memoria)
    ListaRespuestas(const ListaRespuestas&) = delete; // Deshabilita el constructor de copia. Evita que crees un objeto nuevo como copia de uno existente
    ListaRespuestas& operator=(const ListaRespuestas&) = delete; // Deshabilita el operador de asignación por copia. Evita que copies el contenido de un objeto en otro objeto que ya ha sido inicializado

    void insertarAlInicio(int id, int idUsuario, const std::string& contenido); // Inserta un nodo al inicio asignando un Id especifico (usado al cargar archivos)
    void agregarNueva(int idUsuario, const std::string& contenido); // Crea y agrega una nueva respuesta asignando un Id correlativo de forma automatica

    // Getters (Metodo para obtener los datos de un atributo)
    int getCantidad() const; // Getter de la cantidad de elementos de la lista
    Respuesta* getCabeza() const; // Getter del puntero al primer nodo de la lista

    void eliminarPorUsuario(int idUsuario); // Elimina de la lista todas las respuestas de un usuario
    void contarPorUsuario(std::map<int, int>& conteo) const; // Acumula en un mapa las respuestas creadas
    std::string aCSV() const; // Convierte la lista enlazada a una cadena formateada para guardar en CSV

    void liberar(); // Metodo auxiliar que elimina todos los nodos liberando la memoria dinamica
};

#endif // LISTARESPUESTAS_H
