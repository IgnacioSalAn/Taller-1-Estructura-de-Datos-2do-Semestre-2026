#include "Tema.h"

// Constructor (inicializa los atributos por medio de una lista de inicializacion)
Tema::Tema(const std::string& id, const std::string& titulo,
           const std::string& contenido, int idUsuario)
    : id(id), titulo(titulo), contenido(contenido), idUsuario(idUsuario) {}

std::string Tema::getId() const { // Retorna el ID guardado en la instancia del tema
    return id; // Retorna el dato (cadena de texto/string) asociado al ID del tema
} // (numero entero/int)

std::string Tema::getTitulo() const { // Retorna el Titulo guardado en la instancia del tema
    return titulo; // Retorna el dato (cadena de texto/string) asociado al titulo del tema
}

std::string Tema::getContenido() const { // Retorna el Contenido o mensaje principal guardado en la instancia del tema
    return contenido; // Retorna el dato (cadena de texto/string) con el cuerpo del mensaje que responde al tema
}

int Tema::getIdUsuario() const { // Retorna el ID del usuario autor del tema publicado
    return idUsuario; // Retorna el dato (numero entero/int) que representa al autor que responde al tema
}

ListaRespuestas& Tema::getRespuestas() { // Retorna una referencia a la estructura ListaRespuestas asociada a este tema
    return respuestas; // Retorna la referencia a la lista enlazada de respuestas
}
