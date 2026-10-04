//
// Created by Ignacio Salomon on 27-09-26.
//

#include "Tema.h"

#include "../../include/model/Tema.h"
#include <iostream>

Tema::Tema() : id(""), titulo(""), contenido(""), idUsuario(-1) {}

Tema::Tema(std::string id, std::string titulo, std::string contenido, int idUsuario)
    : id(id), titulo(titulo), contenido(contenido), idUsuario(idUsuario) {}

std::string Tema::getId() const { return id; }
std::string Tema::getTitulo() const { return titulo; }
std::string Tema::getContenido() const { return contenido; }
int Tema::getIdUsuario() const { return idUsuario; }

ListaRespuestas& Tema::getRespuestas() { return respuestas; }

void Tema::mostrarInformacion() const {
    std::cout << "ID Tema: " << id << " | Título: " << titulo << "\n";
    std::cout << "Autor (ID): " << idUsuario << "\n";
    std::cout << "Contenido: " << contenido << "\n";
}
