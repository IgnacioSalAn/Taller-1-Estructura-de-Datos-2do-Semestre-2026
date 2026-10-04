cmake_minimum_required(VERSION 3.16)
project(Taller1_ForoComunitario)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Taller1_ForoComunitario
        src/main.cpp
        src/Usuario.cpp
        src/Respuesta.cpp
        src/ListaRespuestas.cpp
        src/Tema.cpp
        src/ArregloUsuarios.cpp
        src/ArregloTemas.cpp
        src/Utilidades.cpp
        src/Foro.cpp
)

target_include_directories(Taller1_ForoComunitario PRIVATE src)

# Copia los archivos CSV de entrada junto al ejecutable para poder
# ejecutar el programa directamente desde CLion sin configurar el
# directorio de trabajo manualmente.
add_custom_command(TARGET Taller1_ForoComunitario POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_SOURCE_DIR}/usuarios.csv
                $<TARGET_FILE_DIR:Taller1_ForoComunitario>/usuarios.csv
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_SOURCE_DIR}/temas.csv
                $<TARGET_FILE_DIR:Taller1_ForoComunitario>/temas.csv
)
