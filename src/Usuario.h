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
class Usuario {
private:
    int id;
    std::string nombre;

public:
    Usuario(int id, const std::string& nombre);

    int getId() const;
    std::string getNombre() const;

    void setNombre(const std::string& nombre);
};

#endif // USUARIO_H
