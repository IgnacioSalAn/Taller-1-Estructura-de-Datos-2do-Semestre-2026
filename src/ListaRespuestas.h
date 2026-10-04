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
private:
    Respuesta* cabeza;
    int cantidad;
    int siguienteId; // proximo id correlativo a asignar dentro de este tema

public:
    ListaRespuestas();
    ~ListaRespuestas();

    // No se permite copiar (evita doble liberacion de memoria)
    ListaRespuestas(const ListaRespuestas&) = delete;
    ListaRespuestas& operator=(const ListaRespuestas&) = delete;

    void insertarAlInicio(int id, int idUsuario, const std::string& contenido);
    void agregarNueva(int idUsuario, const std::string& contenido);

    int getCantidad() const;
    Respuesta* getCabeza() const;

    void eliminarPorUsuario(int idUsuario);
    void contarPorUsuario(std::map<int, int>& conteo) const;
    std::string aCSV() const;

    void liberar();
};

#endif // LISTARESPUESTAS_H
