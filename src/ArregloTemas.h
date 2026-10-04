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
private:
    Tema** temas;
    int capacidad;
    int cantidad;

    void expandirSiEsNecesario();

public:
    explicit ArregloTemas(int capacidadInicial = 5);
    ~ArregloTemas();

    // No se permite copiar (evita doble liberacion de memoria)
    ArregloTemas(const ArregloTemas&) = delete;
    ArregloTemas& operator=(const ArregloTemas&) = delete;

    void agregarAlInicio(Tema* tema);
    void agregarAlFinal(Tema* tema);
    void moverAlInicio(int indice);

    Tema* buscarPorId(const std::string& id) const;
    int buscarIndicePorId(const std::string& id) const;
    bool existeId(const std::string& id) const;
    bool eliminarEnIndice(int indice);

    int getCantidad() const;
    Tema* obtenerEn(int indice) const;
};

#endif // ARREGLOTEMAS_H
