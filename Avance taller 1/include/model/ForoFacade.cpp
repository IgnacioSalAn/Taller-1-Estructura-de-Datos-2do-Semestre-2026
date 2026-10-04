//
// Created by Ignacio Salomon on 29-09-26.
//

#include "../service/ForoFacade.h"

#include "../../include/service/ForoFacade.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

ForoFacade::ForoFacade() : usuarioAutenticado(nullptr) {
    std::srand(std::time(nullptr));
}

void ForoFacade::cargarUsuarios() {
    std::ifstream archivo("usuarios.csv");
    if (!archivo.is_open()) return;

    std::string linea;
    std::getline(archivo, linea); // Encabezado

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string sId, nombre, pass, sRol;

        std::getline(ss, sId, ';');
        std::getline(ss, nombre, ';');
        std::getline(ss, pass, ';');
        std::getline(ss, sRol, ';');

        usuarios.agregar(Usuario(std::stoi(sId), nombre, pass, std::stoi(sRol)));
    }
    archivo.close();
}

void ForoFacade::cargarTemas() {
    std::ifstream archivo("temas.csv");
    if (!archivo.is_open()) return;

    std::string linea;
    std::getline(archivo, linea); // Encabezado

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string idTema, titulo, contenido, sIdUsuario, sRespuestas;

        std::getline(ss, idTema, ';');
        std::getline(ss, titulo, ';');
        std::getline(ss, contenido, ';');
        std::getline(ss, sIdUsuario, ';');
        std::getline(ss, sRespuestas, ';');

        Tema* nuevoTema = new Tema(idTema, titulo, contenido, std::stoi(sIdUsuario));

        // Parsear subcadena de respuestas separadas por comas
        if (!sRespuestas.empty()) {
            std::stringstream ssResp(sRespuestas);
            std::string bloque;
            while (std::getline(ssResp, bloque, ',')) {
                if (bloque.empty()) continue;
                std::stringstream ssBloque(bloque);
                std::string sIdMsg, sIdUsr, txtResp;

                std::getline(ssBloque, sIdMsg, '_');
                std::getline(ssBloque, sIdUsr, '_');
                std::getline(ssBloque, txtResp, '_');

                Respuesta r(std::stoi(sIdMsg), std::stoi(sIdUsr), txtResp);
                nuevoTema->getRespuestas().insertarAlInicio(r);
            }
        }
        temas.agregarAlInicio(nuevoTema);
    }
    archivo.close();
}

void ForoFacade::autenticar() {
    int id;
    std::string pass;
    bool exitoso = false;

    while (!exitoso) {
        std::cout << "=== INICIO DE SESIÓN ===\n";
        std::cout << "ID Usuario: ";
        std::cin >> id;
        std::cout << "Contraseña: ";
        std::cin >> pass;

        Usuario* usr = usuarios.buscarPorId(id);
        if (usr != nullptr && usr->getContrasena() == pass) {
            usuarioAutenticado = usr;
            exitoso = true;
            std::cout << "¡Bienvenido, " << usr->getNombre() << "!\n";
        } else {
            std::cout << "Credenciales incorrectas. Intente de nuevo.\n\n";
        }
    }
}

void ForoFacade::desplegarMenu() {
    char opcion;
    do {
        std::cout << "\n========================================\n";
        std::cout << "          MENÚ PRINCIPAL FORO           \n";
        std::cout << "========================================\n";
        std::cout << "Lista de Temas:\n";

        if (temas.getTamanio() == 0) {
            std::cout << " (No hay temas disponibles)\n";
        } else {
            for (int i = 0; i < temas.getTamanio(); i++) {
                Tema& t = temas.obtener(i);
                std::cout << "[" << i + 1 << "] ID: " << t.getId()
                          << " | Título: " << t.getTitulo()
                          << " (" << t.getRespuestas().getCantidad() << " respuestas)\n";
            }
        }

        std::cout << "\nOpciones:\n";
        std::cout << "A. Revisar tema\n";
        std::cout << "B. Eliminar usuario\n";
        std::cout << "C. Publicar tema\n";
        std::cout << "D. Estadísticas\n";
        std::cout << "E. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        opcion = std::toupper(opcion);

        switch (opcion) {
            case 'A': revisarTema(); break;
            case 'B': eliminarUsuario(); break;
            case 'C': publicarTema(); break;
            case 'D': mostrarEstadisticas(); break;
            case 'E': guardarDatos(); break;
            default: std::cout << "Opción inválida.\n";
        }
    } while (opcion != 'E');
}

void ForoFacade::revisarTema() {
    if (temas.getTamanio() == 0) return;
    int sel;
    std::cout << "Ingrese el número de tema (1 - " << temas.getTamanio() << "): ";
    std::cin >> sel;

    if (sel < 1 || sel > temas.getTamanio()) return;
    int idx = sel - 1;
    Tema& temaSel = temas.obtener(idx);

    temaSel.mostrarInformacion();
    std::cout << "\n--- RESPUESTAS ---\n";
    temaSel.getRespuestas().mostrar();

    char sub;
    std::cout << "\n[A] Comentar | [B] Volver: ";
    std::cin >> sub;

    if (std::toupper(sub) == 'A') {
        std::cin.ignore(10000, '\n');
        std::string txt;
        std::cout << "Escriba su respuesta: ";
        std::getline(std::cin, txt);

        int nuevoIdMsg = temaSel.getRespuestas().getCantidad() + 1;
        Respuesta nuevaR(nuevoIdMsg, usuarioAutenticado->getId(), txt);
        temaSel.getRespuestas().insertarAlInicio(nuevaR);
        temas.moverAlInicio(idx);
        std::cout << "Respuesta agregada y tema movido al inicio.\n";
    }
}

void ForoFacade::eliminarUsuario() {
    int idDel;
    std::cout << "ID del usuario a eliminar: ";
    std::cin >> idDel;

    if (idDel == usuarioAutenticado->getId()) {
        std::cout << "Error: No puede autoeliminarse.\n";
        return;
    }

    Usuario* usr = usuarios.buscarPorId(idDel);
    if (usr == nullptr) return;

    for (int i = 0; i < temas.getTamanio(); i++) {
        temas.obtener(i).getRespuestas().eliminarPorUsuario(idDel);
    }
    for (int i = temas.getTamanio() - 1; i >= 0; i--) {
        if (temas.obtener(i).getIdUsuario() == idDel) {
            temas.eliminarPorIndice(i);
        }
    }
    usuarios.eliminarPorId(idDel);
    std::cout << "Usuario e interacciones eliminados.\n";
}

std::string ForoFacade::generarIdTemaAleatorio() {
    std::string id = "";
    id += (char)('A' + std::rand() % 26);
    id += (char)('A' + std::rand() % 26);
    id += std::to_string(std::rand() % 10);
    id += std::to_string(std::rand() % 10);
    id += std::to_string(std::rand() % 10);
    return id;
}

void ForoFacade::publicarTema() {
    std::cin.ignore(10000, '\n');
    std::string t, c;
    std::cout << "Título: ";
    std::getline(std::cin, t);
    std::cout << "Contenido: ";
    std::getline(std::cin, c);

    Tema* nuevo = new Tema(generarIdTemaAleatorio(), t, c, usuarioAutenticado->getId());
    temas.agregarAlInicio(nuevo);
    std::cout << "Tema publicado con ID: " << nuevo->getId() << "\n";
}

void ForoFacade::mostrarEstadisticas() {
    std::cout << "\n=== ESTADÍSTICAS ===\n";
    std::cout << "1. Expansiones de usuarios: " << usuarios.getExpansiones() << "\n";

    int maxResp = -1;
    for (int i = 0; i < temas.getTamanio(); i++) {
        int cant = temas.obtener(i).getRespuestas().getCantidad();
        if (cant > maxResp) maxResp = cant;
    }

    std::cout << "2. Tema(s) con más respuestas (" << (maxResp > 0 ? maxResp : 0) << "):\n";
    if (maxResp > 0) {
        for (int i = 0; i < temas.getTamanio(); i++) {
            if (temas.obtener(i).getRespuestas().getCantidad() == maxResp) {
                std::cout << "   - " << temas.obtener(i).getTitulo() << "\n";
            }
        }
    }
}

void ForoFacade::guardarDatos() {
    std::ofstream file("temas.csv");
    if (!file.is_open()) return;

    file << "Id;Título;Contenido;IdUsuario;Respuestas\n";
    for (int i = 0; i < temas.getTamanio(); i++) {
        Tema& t = temas.obtener(i);
        file << t.getId() << ";" << t.getTitulo() << ";" << t.getContenido() << ";" << t.getIdUsuario() << ";";

        NodoRespuesta* actual = t.getRespuestas().getCabeza();
        bool primera = true;
        while (actual != nullptr) {
            if (!primera) file << ",";
            file << actual->dato.getIdMensaje() << "_" << actual->dato.getIdUsuario() << "_" << actual->dato.getContenido();
            primera = false;
            actual = actual->siguiente;
        }
        file << "\n";
    }
    file.close();
    std::cout << "Datos guardados en temas.csv.\n";
}