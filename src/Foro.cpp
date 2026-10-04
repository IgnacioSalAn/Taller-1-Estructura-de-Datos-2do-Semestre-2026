#include "Foro.h"
#include "Utilidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>

// Constructor (Guarda las rutas de los archivos CSV y pone el usuario activo en nullptr)
Foro::Foro(const std::string& rutaUsuarios, const std::string& rutaTemas)
    : usuarioActual(nullptr), rutaUsuarios(rutaUsuarios), rutaTemas(rutaTemas) {}

// ---------------------------------------------------------------------
// 2.2 Carga inicial
// ---------------------------------------------------------------------

void Foro::cargarUsuarios() { // Lee el archivo usuarios.csv, valida la integridad de sus campos e inserta los usuarios en el arreglo dinámico
    std::ifstream archivo(rutaUsuarios); // Abre el archivo en modo lectura.
    if (!archivo.is_open()) { // Si el archivo no existe o no se puede abrir:
        std::cerr << "Error: no se pudo abrir el archivo '" << rutaUsuarios << "'." << std::endl;
        std::exit(1); // Detiene la ejecucion inmediatamente como exige la pauta
    }

    std::string linea;
    while (std::getline(archivo, linea)) { // Lee linea por linea
        linea = Utilidades::recortar(linea);
        if (linea.empty()) continue; // Salta lineas vacias

        std::vector<std::string> campos = Utilidades::dividir(linea, ';');
        if (campos.size() != 2) { // Si la linea no tiene exactamente 2 campos:
            std::cerr << "Error: formato invalido en usuarios.csv -> \"" << linea << "\"" << std::endl;
            std::exit(1);
        }

        std::string idTexto = Utilidades::recortar(campos[0]);
        std::string nombre = Utilidades::recortar(campos[1]);

        if (idTexto.empty() || nombre.empty()) {
            std::cerr << "Error: usuarios.csv contiene un Id o Nombre vacio -> \"" << linea << "\"" << std::endl;
            std::exit(1);
        }
        if (!Utilidades::esNumerico(idTexto)) {
            std::cerr << "Error: el Id de usuario '" << idTexto << "' no es numerico." << std::endl;
            std::exit(1);
        }

        int id = std::atoi(idTexto.c_str()); // Convierte la ID a entero.
        arregloUsuarios.agregar(new Usuario(id, nombre)); // Agrega el nuevo usuario
    }
    archivo.close(); // Cierra el archivo
}

void Foro::cargarTemas() { // Lee el archivo temas.csv, comprueba referencias cruzadas de usuarios e inserta los datos en el sistema
    std::ifstream archivo(rutaTemas); // Abre el archivo de temas
    if (!archivo.is_open()) {
        return; // Si el archivo de temas no existe, el foro inicia simplemente sin temas
    }

    std::string linea;
    while (std::getline(archivo, linea)) { // Lee cada linea de temas
        linea = Utilidades::recortar(linea);
        if (linea.empty()) continue;

        std::vector<std::string> campos = Utilidades::dividir(linea, ';');
        if (campos.size() < 4) { // Valida campos obligatorios
            std::cerr << "Error: formato invalido en temas.csv -> \"" << linea << "\"" << std::endl;
            std::exit(1);
        }

        std::string id = Utilidades::recortar(campos[0]);
        std::string titulo = Utilidades::recortar(campos[1]);
        std::string contenido = Utilidades::recortar(campos[2]);
        std::string idUsuarioTexto = Utilidades::recortar(campos[3]);
        std::string respuestasTexto = (campos.size() >= 5) ? campos[4] : "";

        if (id.empty() || titulo.empty() || contenido.empty() || idUsuarioTexto.empty()) {
            std::cerr << "Error: temas.csv contiene un campo obligatorio vacio -> \"" << linea << "\"" << std::endl;
            std::exit(1);
        }
        if (!Utilidades::esIdTemaValido(id)) {
            std::cerr << "Error: el Id de tema '" << id
                      << "' no cumple el formato exigido (2 letras mayusculas + 3 digitos)." << std::endl;
            std::exit(1);
        }
        if (arregloTemas.existeId(id)) {
            std::cerr << "Error: el Id de tema '" << id << "' esta duplicado en temas.csv." << std::endl;
            std::exit(1);
        }
        if (!Utilidades::esNumerico(idUsuarioTexto)) {
            std::cerr << "Error: el IdUsuario '" << idUsuarioTexto << "' del tema '" << id << "' no es numerico." << std::endl;
            std::exit(1);
        }

        int idUsuario = std::atoi(idUsuarioTexto.c_str());
        if (arregloUsuarios.buscarPorId(idUsuario) == nullptr) { // Verifica discrepancia de autor inexistente
            std::cerr << "Error: discrepancia entre temas.csv y usuarios.csv -> el tema '" << id
                      << "' pertenece al usuario " << idUsuario << ", que no existe en usuarios.csv." << std::endl;
            std::exit(1);
        }

        Tema* tema = new Tema(id, titulo, contenido, idUsuario);

        std::string respuestasRecortadas = Utilidades::recortar(respuestasTexto);
        if (!respuestasRecortadas.empty()) {
            std::vector<std::string> mensajes = Utilidades::dividir(respuestasRecortadas, ',');

            // Se insertan en orden inverso: como cada insertarAlInicio pone el elemento en la cabeza, insertar de atras hacia adelante deja la lista final (cabeza -> cola) en el mismo orden del archivo.
            for (int i = static_cast<int>(mensajes.size()) - 1; i >= 0; i--) {
                std::string msg = Utilidades::recortar(mensajes[i]);
                if (msg.empty()) continue;

                size_t primerGuion = msg.find('_');
                size_t segundoGuion = (primerGuion == std::string::npos)
                                          ? std::string::npos
                                          : msg.find('_', primerGuion + 1);

                if (primerGuion == std::string::npos || segundoGuion == std::string::npos) {
                    std::cerr << "Error: formato de respuesta invalido en el tema '" << id
                              << "' -> \"" << msg << "\"" << std::endl;
                    std::exit(1);
                }

                std::string idRespTexto = msg.substr(0, primerGuion);
                std::string idUsuarioRespTexto = msg.substr(primerGuion + 1, segundoGuion - primerGuion - 1);
                std::string contenidoResp = msg.substr(segundoGuion + 1);

                if (!Utilidades::esNumerico(idRespTexto) || !Utilidades::esNumerico(idUsuarioRespTexto)) {
                    std::cerr << "Error: respuesta con id o idUsuario no numerico en el tema '" << id << "'." << std::endl;
                    std::exit(1);
                }

                int idResp = std::atoi(idRespTexto.c_str());
                int idUsuarioResp = std::atoi(idUsuarioRespTexto.c_str());

                if (arregloUsuarios.buscarPorId(idUsuarioResp) == nullptr) {
                    std::cerr << "Error: discrepancia entre temas.csv y usuarios.csv -> una respuesta del tema '"
                              << id << "' pertenece al usuario " << idUsuarioResp << ", que no existe." << std::endl;
                    std::exit(1);
                }

                tema->getRespuestas().insertarAlInicio(idResp, idUsuarioResp, contenidoResp);
            }
        }

        arregloTemas.agregarAlFinal(tema); // Agrega respetando el orden del archivo
    }
    archivo.close();
}

// ---------------------------------------------------------------------
// 2.3 Autenticacion
// ---------------------------------------------------------------------

void Foro::autenticar() { // Solicita el ID del usuario en consola para iniciar sesion en la aplicacion.
    while (true) {
        std::cout << "\n[---------- Foro Comunitario ----------]\n";
        std::cout << "Ingrese su numero de usuario: ";
        std::string entrada;
        std::getline(std::cin, entrada);
        entrada = Utilidades::recortar(entrada);

        if (!Utilidades::esNumerico(entrada)) {
            std::cout << "Error: debe ingresar un Id numerico valido." << std::endl;
            continue;
        }

        int id = std::atoi(entrada.c_str());
        Usuario* usuario = arregloUsuarios.buscarPorId(id);
        if (usuario == nullptr) {
            std::cout << "Error: usuario no encontrado" << std::endl;
            continue;
        }

        usuarioActual = usuario; // Asigna la sesion activa
        std::cout << "Bienvenido/a " << usuario->getNombre() << std::endl;
        break;
    }
}

// ---------------------------------------------------------------------
// 2.4 Menu principal
// ---------------------------------------------------------------------

void Foro::mostrarTemas() const { // Muestra el menu principal de opciones en la consola
    std::cout << "\n[---------- Foro Comunitario ----------]\n\n";
    std::cout << "Temas:\n";
    for (int i = 0; i < arregloTemas.getCantidad(); i++) {
        Tema* t = arregloTemas.obtenerEn(i);
        std::cout << t->getId() << ". " << t->getTitulo() << "\n";
    }
    std::cout << "\nA) Revisar un tema\n";
    std::cout << "B) Eliminar usuario\n";
    std::cout << "C) Publicar\n";
    std::cout << "D) Estadisticas\n";
    std::cout << "E) Salir\n";
}

void Foro::mostrarMenuPrincipal() { // Bucle interactivo para la eleccion de opciones en el menu principal
    bool salir = false;
    while (!salir) {
        mostrarTemas();
        std::cout << "\nSeleccione una opcion: ";
        std::string opcion;
        std::getline(std::cin, opcion);
        opcion = Utilidades::recortar(opcion);

        if (opcion.size() != 1) {
            std::cout << "Error: ingrese una unica opcion valida (A, B, C, D o E)." << std::endl;
            continue;
        }

        char letra = static_cast<char>(std::toupper(static_cast<unsigned char>(opcion[0])));
        switch (letra) {
            case 'A': revisarTema(); break;
            case 'B': eliminarUsuario(); break;
            case 'C': publicarTema(); break;
            case 'D': mostrarEstadisticas(); break;
            case 'E': salir = true; break;
            default:
                std::cout << "Error: opcion no reconocida. Intente nuevamente." << std::endl;
        }
    }
}

// ---------------------------------------------------------------------
// A. Revisar un tema
// ---------------------------------------------------------------------

void Foro::revisarTema() { // Opcion A: Despliega un tema, permite leer sus respuestas y comentarlo (desplazandolo al inicio)
    std::cout << "\n[---------- Foro Comunitario ----------]\n\n";
    std::cout << "Ingrese el Id del tema que desea revisar: ";
    std::string id;
    std::getline(std::cin, id);
    id = Utilidades::recortar(id);

    Tema* tema = arregloTemas.buscarPorId(id);
    if (tema == nullptr) {
        std::cout << "Error: el tema '" << id << "' no existe." << std::endl;
        return;
    }

    bool volverAlMenu = false;
    while (!volverAlMenu) {
        Usuario* autor = arregloUsuarios.buscarPorId(tema->getIdUsuario());

        std::cout << "\n[---------- Foro Comunitario ----------]\n\n";
        std::cout << "Titulo: " << tema->getTitulo() << "\n";
        std::cout << "Usuario: " << (autor != nullptr ? autor->getNombre() : "Desconocido") << "\n\n";
        std::cout << tema->getContenido() << "\n\n";

        Respuesta* actual = tema->getRespuestas().getCabeza();
        while (actual != nullptr) {
            Usuario* usuarioResp = arregloUsuarios.buscarPorId(actual->getIdUsuario());
            std::cout << "Usuario " << (usuarioResp != nullptr ? usuarioResp->getNombre() : "Desconocido")
                      << " responde:\n";
            std::cout << actual->getContenido() << "\n\n";
            actual = actual->getSiguiente();
        }

        std::cout << "A) Comentar\n";
        std::cout << "B) Atras\n";
        std::cout << "Seleccione una opcion: ";
        std::string opcion;
        std::getline(std::cin, opcion);
        opcion = Utilidades::recortar(opcion);

        if (opcion.size() != 1) {
            std::cout << "Error: ingrese una opcion valida (A o B)." << std::endl;
            continue;
        }

        char letra = static_cast<char>(std::toupper(static_cast<unsigned char>(opcion[0])));
        if (letra == 'A') {
            comentarTema(tema);
            int indice = arregloTemas.buscarIndicePorId(tema->getId());
            arregloTemas.moverAlInicio(indice);
        } else if (letra == 'B') {
            volverAlMenu = true;
        } else {
            std::cout << "Error: opcion no reconocida." << std::endl;
        }
    }
}

void Foro::comentarTema(Tema* tema) { // Valida e inserta un nuevo comentario dentro de la lista de respuestas de un tema
    std::cout << "\nIngrese su comentario: ";
    std::string contenido;
    std::getline(std::cin, contenido);
    while (true) {
        if (Utilidades::recortar(contenido).empty()) {
            std::cout << "Error: el comentario no puede estar vacio. Ingrese su comentario: ";
        } else if (contenido.find(',') != std::string::npos || contenido.find('_') != std::string::npos) {
            std::cout << "Error: el comentario no puede contener comas ni guiones bajos. Ingrese su comentario: ";
        } else {
            break;
        }
        std::getline(std::cin, contenido);
    }
    tema->getRespuestas().agregarNueva(usuarioActual->getId(), contenido);
}

// ---------------------------------------------------------------------
// B. Eliminar usuario
// ---------------------------------------------------------------------

void Foro::eliminarUsuario() { // Opcion B: Elimina un usuario especifico, eliminando sus publicaciones y respuestas en cascada
    std::cout << "\n[---------- Foro Comunitario ----------]\n\n";
    std::cout << "Usuarios:\n";
    for (int i = 0; i < arregloUsuarios.getCantidad(); i++) {
        Usuario* u = arregloUsuarios.obtenerEn(i);
        std::cout << u->getId() << ". " << u->getNombre() << "\n";
    }

    std::cout << "\nIngrese el Id del usuario que desea eliminar: ";
    std::string entrada;
    std::getline(std::cin, entrada);
    entrada = Utilidades::recortar(entrada);

    if (!Utilidades::esNumerico(entrada)) {
        std::cout << "Error: debe ingresar un Id numerico valido." << std::endl;
        return;
    }
    int id = std::atoi(entrada.c_str());

    if (id == usuarioActual->getId()) {
        std::cout << "No puedes eliminarte a ti mismo" << std::endl;
        return;
    }

    Usuario* usuario = arregloUsuarios.buscarPorId(id); // Valida autoevaluacion / autoeliminacion.
    if (usuario == nullptr) {
        std::cout << "Error: usuario no encontrado" << std::endl;
        return;
    }

    int temasCreados = 0;
    int respuestasRealizadas = 0;
    for (int i = 0; i < arregloTemas.getCantidad(); i++) {
        Tema* t = arregloTemas.obtenerEn(i);
        if (t->getIdUsuario() == id) {
            temasCreados++;
        }
        Respuesta* r = t->getRespuestas().getCabeza();
        while (r != nullptr) {
            if (r->getIdUsuario() == id) {
                respuestasRealizadas++;
            }
            r = r->getSiguiente();
        }
    }

    std::string nombre = usuario->getNombre();
    std::cout << "\nEl usuario " << nombre << " ha creado " << temasCreados
              << " tema(s) y ha realizado " << respuestasRealizadas << " respuesta(s) en el foro.\n";
    std::cout << "Confirma la eliminacion? (S/N): ";
    std::string confirmacion;
    std::getline(std::cin, confirmacion);
    confirmacion = Utilidades::recortar(confirmacion);

    if (confirmacion.empty() || std::toupper(static_cast<unsigned char>(confirmacion[0])) != 'S') {
        std::cout << "Operacion cancelada." << std::endl;
        return;
    }

    // a. Eliminar los temas publicados por el usuario (junto a sus respuestas)
    for (int i = arregloTemas.getCantidad() - 1; i >= 0; i--) {
        Tema* t = arregloTemas.obtenerEn(i);
        if (t->getIdUsuario() == id) {
            arregloTemas.eliminarEnIndice(i);
        }
    }

    // b. Eliminar las respuestas del usuario en temas de otros usuarios
    for (int i = 0; i < arregloTemas.getCantidad(); i++) {
        arregloTemas.obtenerEn(i)->getRespuestas().eliminarPorUsuario(id);
    }

    arregloUsuarios.eliminarPorId(id);
    std::cout << "Usuario " << nombre << " eliminado con exito" << std::endl;
}

// ---------------------------------------------------------------------
// C. Publicar
// ---------------------------------------------------------------------

std::string Foro::generarIdTemaUnico() const { // Genera un ID aleatorio garantizando la no duplicidad dentro de los temas existentes
    std::string id;
    do {
        id = Utilidades::generarIdAleatorio();
    } while (arregloTemas.existeId(id));
    return id;
}

void Foro::publicarTema() { // Opcion C: Permite publicar un nuevo tema ubicandolo al inicio (indice 0) del arreglo dinamico.
    std::cout << "\n[---------- Foro Comunitario ----------]\n\n";

    std::string titulo;
    std::cout << "Ingrese el titulo: ";
    std::getline(std::cin, titulo);
    while (true) {
        if (Utilidades::recortar(titulo).empty()) {
            std::cout << "Error: el titulo no puede estar vacio. Ingrese el titulo: ";
        } else if (titulo.find(';') != std::string::npos) {
            std::cout << "Error: el titulo no puede contener ';'. Ingrese el titulo: ";
        } else {
            break;
        }
        std::getline(std::cin, titulo);
    }

    std::string contenido;
    std::cout << "Ingrese el contenido: ";
    std::getline(std::cin, contenido);
    while (true) {
        if (Utilidades::recortar(contenido).empty()) {
            std::cout << "Error: el contenido no puede estar vacio. Ingrese el contenido: ";
        } else if (contenido.find(';') != std::string::npos) {
            std::cout << "Error: el contenido no puede contener ';'. Ingrese el contenido: ";
        } else {
            break;
        }
        std::getline(std::cin, contenido);
    }

    std::string id = generarIdTemaUnico();
    Tema* tema = new Tema(id, titulo, contenido, usuarioActual->getId());
    arregloTemas.agregarAlInicio(tema);

    std::cout << "\nTema publicado con ID " << id << std::endl;
}

// ---------------------------------------------------------------------
// D. Estadisticas
// ---------------------------------------------------------------------

void Foro::mostrarEstadisticas() const {
    std::cout << "\n[---------- Foro Comunitario ----------]\n\n";

    // a. Usuario(s) con mas respuestas (usando exclusivamente nuestras estructuras de datos)
    int maxRespuestas = 0;
    for (int i = 0; i < arregloUsuarios.getCantidad(); i++) {
        int idU = arregloUsuarios.obtenerEn(i)->getId();
        int totalU = 0;
        for (int j = 0; j < arregloTemas.getCantidad(); j++) {
            totalU += arregloTemas.obtenerEn(j)->getRespuestas().contarRespuestasDeUsuario(idU);
        }
        if (totalU > maxRespuestas) {
            maxRespuestas = totalU;
        }
    }

    std::cout << "Usuario(s) con mas respuestas:\n";
    if (maxRespuestas == 0) {
        std::cout << "  (No hay respuestas registradas en el foro)\n";
    } else {
        for (int i = 0; i < arregloUsuarios.getCantidad(); i++) {
            Usuario* u = arregloUsuarios.obtenerEn(i);
            int totalU = 0;
            for (int j = 0; j < arregloTemas.getCantidad(); j++) {
                totalU += arregloTemas.obtenerEn(j)->getRespuestas().contarRespuestasDeUsuario(u->getId());
            }
            if (totalU == maxRespuestas) {
                std::cout << "  Id: " << u->getId()
                          << " | Nombre: " << u->getNombre()
                          << " | Respuestas: " << totalU << "\n";
            }
        }
    }

    // b. Tema(s) con mayor cantidad de respuestas
    int maxTema = 0;
    for (int i = 0; i < arregloTemas.getCantidad(); i++) {
        int cant = arregloTemas.obtenerEn(i)->getRespuestas().getCantidad();
        if (cant > maxTema) {
            maxTema = cant;
        }
    }

    std::cout << "\nTema(s) con mayor cantidad de respuestas:\n";
    if (maxTema == 0) {
        std::cout << "  (No hay temas con respuestas registradas)\n";
    } else {
        for (int i = 0; i < arregloTemas.getCantidad(); i++) {
            Tema* t = arregloTemas.obtenerEn(i);
            if (t->getRespuestas().getCantidad() == maxTema) {
                Usuario* autor = arregloUsuarios.buscarPorId(t->getIdUsuario());
                std::cout << "  Id: " << t->getId() << " | Titulo: " << t->getTitulo()
                          << " | Autor: " << (autor != nullptr ? autor->getNombre() : "Desconocido")
                          << " | Respuestas: " << maxTema << "\n";
            }
        }
    }

    // c. Numero de expansiones del arreglo dinamico de usuarios
    std::cout << "\nNumero de expansiones del arreglo de usuarios: "
              << arregloUsuarios.getExpansiones() << std::endl;
}

void Foro::guardarTemas() const { // Guarda los datos de temas y respuestas formateados en el archivo temas.csv al salir.
    std::ofstream archivo(rutaTemas);
    for (int i = 0; i < arregloTemas.getCantidad(); i++) {
        Tema* t = arregloTemas.obtenerEn(i);
        archivo << t->getId() << ";" << t->getTitulo() << ";" << t->getContenido()
                << ";" << t->getIdUsuario() << ";" << t->getRespuestas().aCSV() << "\n";
    }
    archivo.close();
}

// ---------------------------------------------------------------------
// Flujo principal
// ---------------------------------------------------------------------

void Foro::ejecutar() { // Inicia la secuencia completa de la aplicacion Foro.
    cargarUsuarios();
    cargarTemas();
    autenticar();
    mostrarMenuPrincipal();

    guardarTemas();
    std::cout << "\nInformacion guardada en '" << rutaTemas << "'. Hasta pronto!" << std::endl;

    // La memoria de usuarios, temas y respuestas se libera automaticamente
    // gracias a los destructores de ArregloUsuarios, ArregloTemas y
    // ListaRespuestas cuando este objeto Foro sale de alcance en main().
}
