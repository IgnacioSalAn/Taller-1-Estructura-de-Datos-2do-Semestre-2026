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
int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Foro foro("usuarios.csv", "temas.csv");
    foro.ejecutar();

    return 0;
}
