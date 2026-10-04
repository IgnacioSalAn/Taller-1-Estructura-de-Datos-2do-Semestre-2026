#ifndef USUARIO_H
#define USUARIO_H

#include <string>

/**
 * @brief Representa un usuario del foro comunitario.
 *
 * Cada usuario posee un identificador unico (correlativo, leido desde
 * usuarios.csv) y un nombre. Esta clase respeta el encapsulamiento:
 * sus atributos son privados y se accede a ellos mediante getters.
 */
class Usuario { // Clase Usuario
private: // Metodos privados (solo se pueden modificar desde dentro de la clase)
    int id; // Atributo de ID de usuario
    std::string nombre; // Atributo de nombre de usuario

public: // Metodos publicos (accesibles desde cualquier parte del programa)
    Usuario(int id, const std::string& nombre); // Constructor parametrizado para inicializar al usuario

    // Getters (Metodo para obtener los datos de un atributo)
    int getId() const; // Getter del ID del usuario
    std::string getNombre() const; // Getter del nombre del usuario

    // Setter (Metodo para modificar los datos de un atributo)
    void setNombre(const std::string& nombre);
};

#endif // USUARIO_H
