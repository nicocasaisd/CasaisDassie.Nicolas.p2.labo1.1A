/*
 * menu.c
 *
 *  Created on: 10 jun. 2022
 *      Author: nicocasaisd
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "menu.h"
#include "eMovie.h"

/// @fn int menu()
/// @brief Imprime el menu principal y permite que el usuario ingrese una opcion valida
///
/// @return Devuelve un entero con la opcion
int menu()
{
    int opcion;

    printf(" *** Menu de opciones ***\n\n");
    printf("1- Cargar archivo \n");
    printf("2- Imprimir lista \n");
    printf("3- Asignar ratings \n");
    printf("4- Asignar genero \n");
    printf("5- Filtrar por genero \n");
    printf("6- Ordenar peliculas \n");
    printf("7- Guardar peliculas \n");
    printf("8- Salir \n\n");

    utn_getNumero(&opcion, "Ingrese opcion: ", "Opcion invalida. Ingrese un valor numerico.\n", 1, 8, 5);

    return opcion;
}


/// @fn int menuFiltrado()
/// @brief Imprime el menu para filtrar peliculas y permite que el usuario ingrese una opcion valida
///
/// @return Devuelve un entero con la opcion
int menuFiltrado()
{
    int opcion;

    printf(" *** FILTRAR LISTADO ***\n\n");
    printf("1- Filtrar por genero 'Comedia' \n");
    printf("2- Filtrar por genero 'Drama'\n");
    printf("3- Filtrar por genero 'Accion'\n");
    printf("4- Filtrar por genero 'Terror' \n");
    printf("5- Salir \n\n");

    utn_getNumero(&opcion, "Ingrese opcion: ", "Opcion invalida. Ingrese un valor numerico.\n", 1, 5, 5);

    return opcion;
}

/// @fn void printHeader()
/// @brief Imprime el encabezado para mostrar elementos
///
void printHeader()
{
	printf("  id          Titulo                       Genero                   Ratings\n");
	printf("-------------------------------------------------------------------------------\n");

}

