#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <vector>

/**
 * @brief Funciones de apoyo (parseo de texto, validaciones, generacion de
 * ids) usadas por el resto del programa. No constituyen una de las
 * estructuras de datos obligatorias del taller, solo son herramientas
 * auxiliares de manejo de strings.
 */
namespace Utilidades {
    std::vector<std::string> dividir(const std::string& texto, char delimitador);
    std::string recortar(const std::string& texto);
    bool esNumerico(const std::string& texto);
    bool esIdTemaValido(const std::string& id);
    std::string generarIdAleatorio();
}

#endif // UTILIDADES_H
