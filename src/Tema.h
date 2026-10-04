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
class Tema {
private:
    std::string id;
    std::string titulo;
    std::string contenido;
    int idUsuario;
    ListaRespuestas respuestas;

public:
    Tema(const std::string& id, const std::string& titulo,
         const std::string& contenido, int idUsuario);

    std::string getId() const;
    std::string getTitulo() const;
    std::string getContenido() const;
    int getIdUsuario() const;

    ListaRespuestas& getRespuestas();
};

#endif // TEMA_H
