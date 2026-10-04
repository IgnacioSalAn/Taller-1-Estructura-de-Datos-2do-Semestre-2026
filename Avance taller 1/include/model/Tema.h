//
// Created by Ignacio Salomon on 27-09-26.
//

#ifndef TALLER_1_EST__DATOS__TEMA_H
#define TALLER_1_EST__DATOS__TEMA_H
#include <string>


class Tema { // Clase Temas
    std:: string id; // Atributo Id del tema publicado
    std::string titulo; // Atributo Titulo del tema publicado
    std::string contenido; // Atributo Contenido del tema publicado
    int idUsuario; // Atributo Id del usuario del tema publicado
    ListaRespuestas respuestas; // Atributo de la Lista de respuestas acumuladas sobre un tema publicado (Estructura basada en Nodos)

public: // Metodos publicos
    Tema(); // Constructor vacio
    Tema(std::string titulo, std::string contenido, int idUsuario); // Constructor parametrizado

    // Getters
    std::string getId() const; // Getter del Id del tema publicado
    std::string getTitulo() const; // Getter del Titulo del tema publicado
    std::string getContenido() const; // Getter del Contenido del tema publicado
    std::string getIdUsuario() const; // Getter del Id del usuario del tema publicado
    ListaRespuestas getRespuestas() const; // Getter de la Lista de respuestas acumuladas sobre un tema publicado

    void mostrarInformacion() const; // Funcion que muestra la informacion de los Temas

};


#endif //TALLER_1_EST__DATOS__TEMA_H
