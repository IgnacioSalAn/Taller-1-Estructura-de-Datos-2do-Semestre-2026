#include "ListaRespuestas.h"
#include <sstream>

ListaRespuestas::ListaRespuestas() : cabeza(nullptr), cantidad(0), siguienteId(1) {} // Constructor (Inicializa la cabeza en nullptr, el contador en 0 y el correlativo inicial en 1)

ListaRespuestas::~ListaRespuestas() { // Destructor (invoca al metodo liberar para borrar los nodos dinámicos)
    liberar(); // Llama a la funcion de limpieza
}

void ListaRespuestas::insertarAlInicio(int id, int idUsuario, const std::string& contenido) { // Inserta un nuevo nodo con datos especificos al inicio de la lista enlazada (en O(1)).
    Respuesta* nuevo = new Respuesta(id, idUsuario, contenido); // Crea el nuevo nodo en el Heap.
    nuevo->setSiguiente(cabeza); // Apunta el 'siguiente' del nuevo nodo al nodo que era la cabeza actual
    cabeza = nuevo; // Establece el nuevo nodo como la nueva cabeza de la lista
    cantidad++; // Aumenta el contador de nodos
    if (id >= siguienteId) { // Mantiene actualizado el proximo ID correlativo
        siguienteId = id + 1; // Ajusta el siguienteId si leemos un ID mayor
    }
}

void ListaRespuestas::agregarNueva(int idUsuario, const std::string& contenido) { // Genera una nueva respuesta asignando automaticamente el correlativo disponible
    insertarAlInicio(siguienteId, idUsuario, contenido); // Llama a la insercion con 'siguienteId'
}

int ListaRespuestas::getCantidad() const { // Retorna la cantidad de respuestas guardadas en la lista
    return cantidad; // Retorna el entero 'cantidad'
}

Respuesta* ListaRespuestas::getCabeza() const { // Retorna la direccion del primer nodo (cabeza)
    return cabeza; // Retorna el puntero 'cabeza'
}

void ListaRespuestas::eliminarPorUsuario(int idUsuario) { // Recorre la lista y elimina todos los nodos pertenecientes a un ID de usuario determinado
    Respuesta* actual = cabeza; // Puntero iterador para recorrer la lista
    Respuesta* anterior = nullptr; // Puntero auxiliar para reestructurar los enlaces

    while (actual != nullptr) { // Recorre la lista hasta llegar al final
        if (actual->getIdUsuario() == idUsuario) { // Si el nodo pertenece al usuario a eliminar:
            Respuesta* aEliminar = actual; // Guarda la direccion del nodo a destruir
            if (anterior == nullptr) { // Caso 1: El nodo a eliminar es la cabeza de la lista
                cabeza = actual->getSiguiente(); // La cabeza pasa a ser el segundo nodo
                actual = cabeza; // Avanza el puntero actual al nuevo inicio
            } else { // Caso 2: El nodo esta en medio o al final de la lista
                anterior->setSiguiente(actual->getSiguiente()); // Salta el nodo actual reconectando el enlace
                actual = actual->getSiguiente(); // Avanza al siguiente nodo
            }
            delete aEliminar; // Libera la memoria del nodo eliminado del Heap
            cantidad--; // Disminuye el total de respuestas de la lista
        } else { // Si el nodo no coincide con el usuario:
            anterior = actual; // Mueve el puntero anterior al nodo actual
            actual = actual->getSiguiente(); // Avanza al siguiente nodo
        }
    }
}

void ListaRespuestas::contarPorUsuario(std::map<int, int>& conteo) const { // Acumula la cantidad de respuestas de cada usuario en un map
    Respuesta* actual = cabeza; // Comienza desde el primer nodo
    while (actual != nullptr) { // Iteracion lineal sobre la lista enlazada
        conteo[actual->getIdUsuario()]++; // Incrementa el contador del usuario en el mapa
        actual = actual->getSiguiente(); // Avanza al siguiente nodo
    }
}

std::string ListaRespuestas::aCSV() const { // Genera la cadena CSV preservando la secuencia cronologica original de los mensajes
    if (cabeza == nullptr) { // Si la lista esta vacia:
        return ""; // Retorna un string vacio
    }

    std::vector<Respuesta*> nodos; // Vector auxiliar para almacenar punteros temporales
    Respuesta* actual = cabeza; // Puntero iterador
    while (actual != nullptr) { // Guarda las direcciones de todos los nodos de cabeza a cola
        nodos.push_back(actual); // Inserta el nodo en el vector temporario
        actual = actual->getSiguiente(); // Avanza al siguiente elemento
    }

    std::ostringstream oss; // Stream para construir el texto resultante
    bool primero = true; // Control de separadores por coma
    // Recorre el vector en orden inverso (de la respuesta mas antigua a la mas reciente):
    for (int i = static_cast<int>(nodos.size()) - 1; i >= 0; i--) {
        if (!primero) {
            oss << ","; // Imprime coma entre respuestas
        }
        oss << nodos[i]->getId() << "_"
            << nodos[i]->getIdUsuario() << "_"
            << nodos[i]->getContenido(); // Agrega la respuesta formateada ID_Usuario_Mensaje
        primero = false;
    }
    return oss.str(); // Devuelve la cadena armada
}

void ListaRespuestas::liberar() { // Borra secuencialmente todos los nodos de la lista para evitar fugas de memoria
    Respuesta* actual = cabeza; // Comienza por la cabeza.
    while (actual != nullptr) { // Mientras queden nodos por destruir:
        Respuesta* siguienteNodo = actual->getSiguiente(); // Respaldamos el puntero al siguiente nodo.
        delete actual; // Liberamos el nodo actual.
        actual = siguienteNodo; // Avanzamos a la posicion respaldada.
    }
    cabeza = nullptr; // Reiniciamos el puntero cabeza a nulo.
    cantidad = 0; // Reiniciamos el contador a cero.
}
