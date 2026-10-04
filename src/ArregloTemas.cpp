#include "ArregloTemas.h"
#include <cstdlib>

// Constructor (reserva memoria dinamica inicial usando malloc para el arreglo de punteros a Tema)
ArregloTemas::ArregloTemas(int capacidadInicial) // Se instancia el arreglo, el tamanio del arreglo comienza siendo la capacidad inicial
    : capacidad(capacidadInicial), cantidad(0) { // Se establecen los valores iniciales a los atributos de la clase instanciaciada
    temas = static_cast<Tema**>(malloc(sizeof(Tema*) * capacidad)); // Asigna el bloque inicial en el heap
}

ArregloTemas::~ArregloTemas() { // Destructor (ecorre el arreglo liberando cada objeto Tema y luego libera el arreglo de punteros)
    for (int i = 0; i < cantidad; i++) { // Itera sobre cada tema guardado
        delete temas[i]; // Libera el objeto Tema de la memoria dinamica con delete
    }
    free(temas); // Libera el bloque del arreglo dinamico reservado con malloc/realloc
}

void ArregloTemas::expandirSiEsNecesario() { // Metodo privado que duplica la memoria asignada si la cantidad de elementos alcanza la capacidad
    if (cantidad == capacidad) { // Verifica si el arreglo alcanzo su capacidad limite
        capacidad *= 2; // Duplica la capacidad actual del arreglo
        temas = static_cast<Tema**>(realloc(temas, sizeof(Tema*) * capacidad)); // Utiliza realloc para redimensionar el arreglo en el heap manteniendo los punteros existentes
    }
}

void ArregloTemas::agregarAlInicio(Tema* tema) { // Inserta un tema en la primera posicion (indice 0) desplanzando todo el resto hacia la derecha.
    expandirSiEsNecesario(); // Asegura que exista espacio disponible.
    for (int i = cantidad; i > 0; i--) { // Recorre el arreglo desde el final hacia atras
        temas[i] = temas[i - 1]; // Desplaza cada puntero una posicion a la derecha
    }
    temas[0] = tema; // Asigna el nuevo tema en el indice 0
    cantidad++; // Incrementa la cantidad total de temas registrados
}

void ArregloTemas::agregarAlFinal(Tema* tema) { // Agrega un tema en el ultimo indice disponible (mantiene el orden al leer el CSV)
    expandirSiEsNecesario(); // Asegura que exista espacio disponible
    temas[cantidad] = tema; // Asigna el tema al final del arreglo
    cantidad++; // Incrementa el contador de temas
}

void ArregloTemas::moverAlInicio(int indice) { // Traslada un tema existente desde su posicion actual hasta el inicio (indice 0) al ser comentado
    if (indice <= 0 || indice >= cantidad) { // Valida que el indice exista y no sea ya el primero
        return; // Sale si la posicion no requiere movimiento
    }
    Tema* tema = temas[indice]; // Guarda temporalmente el puntero del tema a mover
    for (int i = indice; i > 0; i--) { // Desplaza los temas anteriores un espacio a la derecha
        temas[i] = temas[i - 1]; // Copia el puntero previo en el indice actual
    }
    temas[0] = tema; // Coloca el tema respaldado al inicio del arreglo
}

int ArregloTemas::buscarIndicePorId(const std::string& id) const { // Busca la posicion en el arreglo de un tema segun su ID alfanumerico
    for (int i = 0; i < cantidad; i++) { // Recorre el arreglo de temas
        if (temas[i]->getId() == id) { // Compara el Id del tema actual con el buscado
            return i; // Retorna la posicion del tema si lo encuentra
        }
    }
    return -1; // Retorna -1 si el tema no existe
}

Tema* ArregloTemas::buscarPorId(const std::string& id) const { // Busca y retorna la direccion del objeto Tema segun su ID
    int indice = buscarIndicePorId(id); // Obtiene la posicion del tema
    return (indice == -1) ? nullptr : temas[indice]; // Retorna el puntero o nullptr si no fue hallado
}

bool ArregloTemas::existeId(const std::string& id) const { // Retorna verdadero si la ID de un tema ya esta en uso.
    return buscarIndicePorId(id) != -1; // Verifica si el indice es distinto de -1
}

bool ArregloTemas::eliminarEnIndice(int indice) { // Elimina un tema segun su posicion y desplaza los elementos subsiguientes a la izquierda.
    if (indice < 0 || indice >= cantidad) { // Comprueba que el indice sea valido
        return false; // Retorna false si esta fuera de rango
    }
    delete temas[indice]; // Libera de la memoria el objeto Tema seleccionado
    for (int i = indice; i < cantidad - 1; i++) { // Recorre los elementos posteriores
        temas[i] = temas[i + 1]; // Traslada cada puntero un espacio a la izquierda
    }
    cantidad--; // Reduce el numero de temas almacenados
    return true; // Retorna verdadero indicando exito
}

int ArregloTemas::getCantidad() const { // Retorna la cantidad total de temas guardados en el arreglo
    return cantidad; // Retorna el entero 'cantidad'
}

Tema* ArregloTemas::obtenerEn(int indice) const { // Retorna el puntero al tema alojado en un indice en particular
    if (indice < 0 || indice >= cantidad) { // Valida los limites del indice
        return nullptr; // Retorna nullptr si la posicion es invalida
    }
    return temas[indice]; // Retorna el puntero al Tema en la posicion indicada
}
