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
    std::vector<std::string> dividir(const std::string& texto, char delimitador); // Divide un texto en partes segun un caracter delimitador
    std::string recortar(const std::string& texto); // Elimina espacios en blanco y saltos de linea al inicio y final
    bool esNumerico(const std::string& texto); // Comprueba si una cadena esta formada unicamente por digitos numericos
    bool esIdTemaValido(const std::string& id); // Valida que una ID cumpla el formato de 2 letras mayusculas y 3 digitos
    std::string generarIdAleatorio(); // Genera una nueva ID aleatoria valida para publicaciones nuevas
}

#endif // UTILIDADES_H
