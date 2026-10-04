//
// Created by Ignacio Salomon on 27-09-26.
//

#ifndef TALLER_1_EST__DATOS__RESPUESTA_H
#define TALLER_1_EST__DATOS__RESPUESTA_H
#include <string>


class Respuesta { // Clase Usuario
    int idMensaje; // Atributo de Id de Mensaje de respuesta
    int idUsuario; // Atributo de Id de Usuario que responde
    std::string contenido; // Atributo de Contenido de Mensaje de respuesta

public: // Metodos
    Respuesta(); // Constructor vacio
    Respuesta(int idMensaje, int idUsuario, std::string contenido); // Constructor parametrizado

    // Getters
    int getIdMensaje() const; // Getter del Id del mensaje de respuesta
    int getIdUsuario() const; // Getter del Nombre del usuario que responde
    std::string getContenido() const; // Getter del Contenido de Mensaje de respuesta

};


#endif //TALLER_1_EST__DATOS__RESPUESTA_H
