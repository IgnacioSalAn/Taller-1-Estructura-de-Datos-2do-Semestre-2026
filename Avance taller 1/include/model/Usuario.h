//
// Created by Ignacio Salomon on 27-09-26.
//

#ifndef TALLER_1_EST__DATOS__USUARIO_H
#define TALLER_1_EST__DATOS__USUARIO_H

#include <iostream>

class Usuario { // Clase Usuario
    int id; // Atributo de ID
    std:: string nombre; // Atributo de nombre
};

public: // Metodos publicos
    Usuario(); // Constructor vacio
    Usuario(int id, std::string nombre); // Constructor parametrizado

    // Getters
    int getId() const; // Getter del Id del usuario
    std:: string getNombre() const; // Getter del Nombre del usuario

    void mostrarInformacion() const;
};

#endif //TALLER_1_EST__DATOS__USUARIO_H
