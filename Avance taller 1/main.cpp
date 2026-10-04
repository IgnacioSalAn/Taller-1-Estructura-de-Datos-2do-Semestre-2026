#include <iostream>

#include "include/service/ForoFacade.h"

int main() {
    ForoFacade foro;
    foro.cargarUsuarios();
    foro.cargarTemas();
    foro.autenticar();
    foro.desplegarMenu();
    return 0;
}