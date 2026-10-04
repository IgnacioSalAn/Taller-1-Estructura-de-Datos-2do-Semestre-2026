#include "Foro.h"
#include <ctime>
#include <cstdlib>

/**
 * @brief Punto de entrada del programa.
 *
 * El metodo main se mantiene deliberadamente sencillo (como exige la
 * rubrica): solo inicializa la semilla aleatoria (usada para generar los
 * ids de los temas publicados) y delega toda la logica a la clase Foro.
 */
int main() { // Punto de entrada principal del sistema.
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Inicializa la semilla aleatoria

    Foro foro("usuarios.csv", "temas.csv"); // Instancia el objeto Foro pasando las rutas de entrada
    foro.ejecutar(); // Delega el flujo completo a la controladora principal

    return 0; // Termina la ejecucion retornando 0 al sistema operativo
}
