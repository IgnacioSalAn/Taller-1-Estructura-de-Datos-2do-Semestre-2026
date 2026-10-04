#include "Utilidades.h"
#include <sstream>
#include <cctype>
#include <cstdlib>

std::vector<std::string> Utilidades::dividir(const std::string& texto, char delimitador) { // Divide un string recibido en subcadenas separadas por el caracter delimitador especificado.
    std::vector<std::string> partes; // Vector contenedor de las partes extraidas
    std::stringstream ss(texto); // Stream de cadena inicializado con el texto de origen
    std::string parte; // Variable temporal para alojar cada fragmento
    while (std::getline(ss, parte, delimitador)) { // Lee hasta encontrar el delimitador
        partes.push_back(parte); // Agrega la subcadena leida al vector
    }
    // Si el texto termina justo en el delimitador, el ultimo campo vacio
    // no es generado por getline, asi que se agrega manualmente.
    if (!texto.empty() && texto.back() == delimitador) { // Maneja el caso borde de un delimitador al final
        partes.push_back(""); // Inserta un elemento vacio al final
    }
    return partes; // Retorna el vector de fragmentos procesados
}

std::string Utilidades::recortar(const std::string& texto) { // Remueve espacios, tabulaciones y saltos de linea sobrantes de ambos extremos de la cadena.
    size_t inicio = texto.find_first_not_of(" \t\r\n"); // Busca el primer caracter que no sea espacio
    if (inicio == std::string::npos) { // Si solo hay espacios o esta vacio:
        return ""; // Retorna una cadena vacia
    }
    size_t fin = texto.find_last_not_of(" \t\r\n"); // Busca el ultimo caracter que no sea espacio
    return texto.substr(inicio, fin - inicio + 1); // Retorna la subcadena limpia
}

bool Utilidades::esNumerico(const std::string& texto) { // Retorna verdadero si la cadena contiene exclusivamente digitos del 0 al 9
    if (texto.empty()) { // Si la cadena esta vacia:
        return false; // Retorna false
    }
    for (char c : texto) { // Recorre cada caracter del texto
        if (!std::isdigit(static_cast<unsigned char>(c))) { // Verifica si el caracter no es digito
            return false; // Retorna false ante cualquier caracter no numerico
        }
    }
    return true; // Retorna verdadero si todos son numeros
}

bool Utilidades::esIdTemaValido(const std::string& id) { // Verifica que una ID de tema tenga exactamente 5 caracteres (2 letras mayusculas y 3 numeros).
    if (id.size() != 5) { // Verifica el largo exacto del texto
        return false; // Retorna false si no mide 5 caracteres
    }
    for (int i = 0; i < 2; i++) { // Revisa las dos primeras posiciones
        if (!std::isupper(static_cast<unsigned char>(id[i]))) { // Comprueba si no son mayusculas
            return false; // Retorna false si no cumple
        }
    }
    for (int i = 2; i < 5; i++) { // Revisa las tres ultimas posiciones
        if (!std::isdigit(static_cast<unsigned char>(id[i]))) { // Comprueba si no son digitos
            return false; // Retorna false si no cumple
        }
    }
    return true; // Retorna verdadero si cumple el formato exigido
}

std::string Utilidades::generarIdAleatorio() { // Genera de forma aleatoria un identificador unico de tema con el formato de 2 letras y 3 numeros.
    std::string id;
    id += static_cast<char>('A' + rand() % 26); // Asigna la primera letra mayuscula aleatoria
    id += static_cast<char>('A' + rand() % 26); // Asigna la segunda letra mayuscula aleatoria
    for (int i = 0; i < 3; i++) { // Genera los tres digitos numéricos aleatorios
        id += static_cast<char>('0' + rand() % 10);
    }
    return id; // Retorna la ID generada
}
