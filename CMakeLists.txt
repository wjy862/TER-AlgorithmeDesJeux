cmake_minimum_required(VERSION 3.19)
project(theorieDesJeux C)

set(CMAKE_C_STANDARD 99)
LINK_LIBRARIES(m)
add_executable(theorieDesJeux main.c benefice.h apprendissage.h jeu.h parametre.h prints.h)