//
// Created by Ignacio Salomon on 27-09-26.
//

#include "Respuesta.h"

Respuesta::Respuesta() : idMensaje(-1), idUsuario(-1), contenido("") {}

Respuesta::Respuesta(int idMensaje, int idUsuario, std::string contenido)
    : idMensaje(idMensaje), idUsuario(idUsuario), contenido(contenido) {}

int Respuesta::getIdMensaje() const { return idMensaje; }
int Respuesta::getIdUsuario() const { return idUsuario; }
std::string Respuesta::getContenido() const { return contenido; }
