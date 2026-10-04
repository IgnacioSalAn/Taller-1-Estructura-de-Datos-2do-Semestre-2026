#include "ArregloUsuarios.h"
#include <cstdlib>

// Constructor (reserva memoria dinamica inicial usando malloc para el arreglo de punteros)
ArregloUsuarios::ArregloUsuarios(int capacidadInicial) // Se instancia el arreglo, el tamanio del arreglo comienza siendo la capacidad inicial
    : capacidad(capacidadInicial), cantidad(0), expansiones(0) { // Se establecen los valores iniciales a los atributos de la clase instanciaciada
    usuarios = static_cast<Usuario**>(malloc(sizeof(Usuario*) * capacidad)); // Asigna el bloque inicial en el heap (hace una reserva de memoria dinamica)
}

// Destructor (recorre el arreglo liberando cada objeto Usuario y luego libera el arreglo completo)
ArregloUsuarios::~ArregloUsuarios() { // Se define el destructor
    for (int i = 0; i < cantidad; i++) { // Itera sobre cada usuario guardado (se recorre el arreglo)
        delete usuarios[i]; // Libera el objeto de la memoria dinamica con delete
    }
    free(usuarios); // Libera el bloque del arreglo dinamico reservado con malloc/realloc
}

void ArregloUsuarios::expandir() { // Metodo privado para reasignar memoria cuando el arreglo se llena
    capacidad *= 2; // Duplica la capacidad actual del arreglo
    Usuario** nuevo = static_cast<Usuario**>(realloc(usuarios, sizeof(Usuario*) * capacidad)); // Utiliza realloc para redimensionar el arreglo a la nueva capacidad
    usuarios = nuevo; // Actualiza el puntero 'usuarios' con la nueva direccion otorgada por realloc
    expansiones++; // Incrementa el registro de veces que el arreglo se ha expandido
}

void ArregloUsuarios::agregar(Usuario* usuario) { // Agrega un nuevo usuario al arreglo
    if (cantidad == capacidad) { // Verifica si el arreglo alcanzo su capacidad limite
        expandir(); // Llama a expandir si ya no hay espacio disponible
    }
    usuarios[cantidad] = usuario; // Asigna el nuevo puntero al ultimo indice vacio
    cantidad++; // Incrementa la cantidad de usuarios registrados
}

int ArregloUsuarios::buscarIndicePorId(int id) const { // Busca la posicion en el arreglo de un usuario segun su ID
    for (int i = 0; i < cantidad; i++) { // Recorre el arreglo secuencialmente
        if (usuarios[i]->getId() == id) { // Compara el Id del usuario actual con el buscado
            return i; // Si lo encuentra, retorna el indice numérico
        }
    }
    return -1; // Retorna -1 si el usuario no existe en el arreglo
}

Usuario* ArregloUsuarios::buscarPorId(int id) const { // Busca y retorna la direccion de memoria del usuario por su ID
    int indice = buscarIndicePorId(id); // Obtiene el indice del usuario
    return (indice == -1) ? nullptr : usuarios[indice]; // Si no existe retorna nullptr, si existe retorna el puntero
}

bool ArregloUsuarios::eliminarPorId(int id) { // Elimina un usuario por su ID y desplaza los elementos restantes para no dejar huecos
    int indice = buscarIndicePorId(id); // Busca la posicion del usuario a eliminar
    if (indice == -1) { // Si el usuario no fue encontrado:
        return false; // Retorna false indicando que no se pudo eliminar
    }
    delete usuarios[indice]; // Libera la memoria del objeto Usuario eliminado
    for (int i = indice; i < cantidad - 1; i++) { // Recorre los elementos posteriores
        usuarios[i] = usuarios[i + 1]; // Desplaza cada puntero una posicion a la izquierda
    }
    cantidad--; // Disminuye en 1 la cantidad total de usuarios activos
    return true; // Retorna verdadero indicando exito
}

int ArregloUsuarios::getCantidad() const { // Retorna la cantidad actual de usuarios almacenados
    return cantidad; // Retorna el entero 'cantidad'
}

int ArregloUsuarios::getExpansiones() const { // Retorna cuantas veces fue necesario expandir la memoria con realloc
    return expansiones; // Retorna el entero 'expansiones'
}

Usuario* ArregloUsuarios::obtenerEn(int indice) const { // Retorna el usuario ubicado en una posicion dada del arreglo
    if (indice < 0 || indice >= cantidad) { // Valida que el indice este dentro del rango permitido
        return nullptr; // Retorna nullptr si la posicion es invalida
    }
    return usuarios[indice]; // Retorna el puntero ubicado en el indice
}
