#ifndef TEMA_H
#define TEMA_H

#include <string>
#include "ListaRespuestas.h"

/**
 * @brief Representa un tema publicado en el foro comunitario.
 *
 * Contiene sus datos basicos (id, titulo, contenido, autor) y la lista
 * enlazada simple con todas las respuestas asociadas a este tema.
 */
class Tema { // Clase Tema
private: // Metodos privados (solo se pueden modificar desde dentro de la clase)
    std::string id; // Atributo ID del tema publicado
    std::string titulo; // Atributo titulo del tema publicado
    std::string contenido; // Atributo contenido del tema publicado
    int idUsuario; // Atributo ID del usuario del tema publicado
    ListaRespuestas respuestas; // Atributo de la lista de respuestas acumuladas sobre un tema publicado (Estructura basada en Nodos)

public: // Metodos publicos
    Tema(const std::string& id, const std::string& titulo,
         const std::string& contenido, int idUsuario); // Constructor parametrizado

    std::string getId() const; // Getter del ID del tema publicado
    std::string getTitulo() const; // Getter del titulo del tema publicado
    std::string getContenido() const; // Getter del contenido del tema publicado
    int getIdUsuario() const; // Getter del id del usuario del tema publicado

    ListaRespuestas& getRespuestas(); // Getter de la Lista de respuestas acumuladas sobre un tema publicado
};

#endif // TEMA_H
