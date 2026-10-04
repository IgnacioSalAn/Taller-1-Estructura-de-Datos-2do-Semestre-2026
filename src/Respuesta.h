#ifndef RESPUESTA_H
#define RESPUESTA_H

#include <string>

/**
 * @brief Nodo de la lista enlazada simple que almacena una respuesta a un tema.
 *
 * Cada nodo guarda su propio id correlativo, el id del usuario que la
 * escribio, el contenido del mensaje y un puntero al siguiente nodo.
 */
class Respuesta {
private:
    int id;
    int idUsuario;
    std::string contenido;
    Respuesta* siguiente;

public:
    Respuesta(int id, int idUsuario, const std::string& contenido);

    int getId() const;
    int getIdUsuario() const;
    std::string getContenido() const;
    Respuesta* getSiguiente() const;

    void setSiguiente(Respuesta* nuevoSiguiente);
};

#endif // RESPUESTA_H
