#ifndef FORO_H
#define FORO_H

#include <string>
#include "ArregloUsuarios.h"
#include "ArregloTemas.h"
#include "Tema.h"

/**
 * @brief Clase principal que controla el flujo de la aplicacion
 * "Foro Comunitario": carga inicial, autenticacion, menu principal y
 * cada una de sus opciones (revisar tema, eliminar usuario, publicar,
 * estadisticas y salir).
 */
class Foro {
private:
    ArregloUsuarios arregloUsuarios;
    ArregloTemas arregloTemas;
    Usuario* usuarioActual;
    std::string rutaUsuarios;
    std::string rutaTemas;

    void cargarUsuarios();
    void cargarTemas();
    void autenticar();

    void mostrarMenuPrincipal();
    void mostrarTemas() const;

    void revisarTema();
    void comentarTema(Tema* tema);
    void eliminarUsuario();
    void publicarTema();
    void mostrarEstadisticas() const;

    void guardarTemas() const;
    std::string generarIdTemaUnico() const;

public:
    Foro(const std::string& rutaUsuarios, const std::string& rutaTemas);
    void ejecutar();
};

#endif // FORO_H
