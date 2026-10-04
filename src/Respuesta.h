#ifndef RESPUESTA_H
#define RESPUESTA_H

#include <string>

/**
 * @brief Nodo de la lista enlazada simple que almacena una respuesta a un tema.
 *
 * Cada nodo guarda su propio id correlativo, el id del usuario que la
 * escribio, el contenido del mensaje y un puntero al siguiente nodo.
 */
class Respuesta { // Clase Respuesta
private: // Metodos privados (solo se pueden modificar desde dentro de la clase)
    int id; // Atributo del ID correspondiente al mensaje de respuesta
    int idUsuario; // Atributo de ID del usuario que escribe la respuesta
    std::string contenido; // Atributo del contenido (la cadena de texto) del mensaje de respuesta a un tema
    Respuesta* siguiente; // Puntero de enlace que apunta al siguiente nodo Respuesta en la lista

public: // Metodos publicos (accesibles desde cualquier parte del programa)
    Respuesta(int id, int idUsuario, const std::string& contenido); // Constructor parametrizado para instanciar un nodo

    int getId() const; // Getter del ID del mensaje de respuesta
    int getIdUsuario() const; // Getter del ID del usuario que responde
    std::string getContenido() const; // Getter del contenido del mensaje de respuesta
    Respuesta* getSiguiente() const; // Getter de la direccion hacia el siguiente nodo enlazado

    void setSiguiente(Respuesta* nuevoSiguiente); // Setter que actualiza el enlace/ cambia hacia siguiente nodo para su uso
};

#endif // RESPUESTA_H
