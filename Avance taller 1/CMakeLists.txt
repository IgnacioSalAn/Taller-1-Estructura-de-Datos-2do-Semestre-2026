cmake_minimum_required(VERSION 4.3)
project(Taller_1_Est__Datos_)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller_1_Est__Datos_ main.cpp
        include/model/Usuario.cpp
        include/model/Usuario.h
        include/model/Respuesta.cpp
        include/model/Respuesta.h
        include/model/Tema.cpp
        include/model/Tema.h
        include/model/NodoRespuesta.cpp
        include/struct/NodoRespuesta.h
        include/model/ListaRespuestas.cpp
        include/struct/ListaRespuestas.h
        include/model/ArregloUsuarios.cpp
        include/struct/ArregloUsuarios.h
        include/model/ArregloTemas.cpp
        include/struct/ArregloTemas.h
        include/model/ForoFacade.cpp
        include/service/ForoFacade.h
)
