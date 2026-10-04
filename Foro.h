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
private: // Metodos privados (solo se pueden modificar desde dentro de la clase)
    ArregloUsuarios arregloUsuarios; // Instancia de la estructura dinamica de usuarios.
    ArregloTemas arregloTemas; // Instancia de la estructura dinamica de temas
    Usuario* usuarioActual; // Puntero al usuario que ha iniciado sesion activa
    std::string rutaUsuarios; // Ruta del archivo usuarios.csv
    std::string rutaTemas; // Ruta del archivo temas.csv

    void cargarUsuarios(); // Carga y valida el archivo usuarios.csv
    void cargarTemas(); // Carga y valida el archivo temas.csv
    void autenticar(); // Maneja el flujo de inicio de sesion por ID de usuario

    void mostrarMenuPrincipal(); // Ciclo principal de navegacion por las opciones
    void mostrarTemas() const; // Muestra la lista de temas en pantalla

    void revisarTema(); // Muestra el contenido y respuestas de un tema
    void comentarTema(Tema* tema); // Agrega una nueva respuesta a un tema
    void eliminarUsuario(); // Elimina en cascada a un usuario y su contenido
    void publicarTema(); // Crea y ubica un nuevo tema al inicio del arreglo
    void mostrarEstadisticas() const; // Genera el reporte de uso del foro

    void guardarTemas() const; // Guarda los temas y sus respuestas en temas.csv
    std::string generarIdTemaUnico() const; // Genera un ID de tema garantizando que no este repetido

public: // Metodos publicos (accesibles desde cualquier parte del programa)
    Foro(const std::string& rutaUsuarios, const std::string& rutaTemas); // Constructor con las rutas de archivos
    void ejecutar(); // Punto de entrada para iniciar la orquestacion de la aplicacion
};

#endif // FORO_H
