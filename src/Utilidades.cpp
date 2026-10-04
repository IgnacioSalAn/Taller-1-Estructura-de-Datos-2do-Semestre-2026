#include "Utilidades.h"
#include <sstream>
#include <cctype>
#include <cstdlib>

std::vector<std::string> Utilidades::dividir(const std::string& texto, char delimitador) {
    std::vector<std::string> partes;
    std::stringstream ss(texto);
    std::string parte;
    while (std::getline(ss, parte, delimitador)) {
        partes.push_back(parte);
    }
    // Si el texto termina justo en el delimitador, el ultimo campo vacio
    // no es generado por getline, asi que se agrega manualmente.
    if (!texto.empty() && texto.back() == delimitador) {
        partes.push_back("");
    }
    return partes;
}

std::string Utilidades::recortar(const std::string& texto) {
    size_t inicio = texto.find_first_not_of(" \t\r\n");
    if (inicio == std::string::npos) {
        return "";
    }
    size_t fin = texto.find_last_not_of(" \t\r\n");
    return texto.substr(inicio, fin - inicio + 1);
}

bool Utilidades::esNumerico(const std::string& texto) {
    if (texto.empty()) {
        return false;
    }
    for (char c : texto) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool Utilidades::esIdTemaValido(const std::string& id) {
    if (id.size() != 5) {
        return false;
    }
    for (int i = 0; i < 2; i++) {
        if (!std::isupper(static_cast<unsigned char>(id[i]))) {
            return false;
        }
    }
    for (int i = 2; i < 5; i++) {
        if (!std::isdigit(static_cast<unsigned char>(id[i]))) {
            return false;
        }
    }
    return true;
}

std::string Utilidades::generarIdAleatorio() {
    std::string id;
    id += static_cast<char>('A' + rand() % 26);
    id += static_cast<char>('A' + rand() % 26);
    for (int i = 0; i < 3; i++) {
        id += static_cast<char>('0' + rand() % 10);
    }
    return id;
}
