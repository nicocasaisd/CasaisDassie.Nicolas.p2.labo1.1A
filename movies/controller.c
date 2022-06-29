#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "eMovie.h"
#include "parser.h"
#include "menu.h"
#include "utn.h"
#include "controller.h"




/** \brief Carga los datos de las peliculas desde el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo
 * \param pList LinkedList* Puntero a LinkedList
 * \return int Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
 *
 */
int controller_loadFromText(char* path , LinkedList* pList)
{
	int exit_status = 0;
	// abro el archivo en un puntero a struct FILE en modo 'read'
	FILE* pFile = fopen(path, "r");
	if(pFile != NULL)
	{
		printf("Cargando desde archivo de texto ... \n");
		// llamo a parser que me lo carga en la LinkedList
		if(parser_eMovieFromText(pFile , pList))
        {
            printf("Se cargo correctamente en memoria.\n");
        }
        else
        {
            printf("Ocurrio un error al intentar parsear el archivo\n");
        }
		// cierro el archivo
		fclose(pFile);
		exit_status = 1;
	}
	else
	{
		printf("Ocurrio un error al cargar el archivo de texto.\n");
	}

    return exit_status;
}

int controller_loadFromText_userInput(LinkedList* pList)
{
    int exit_status = 0;
    char rutaArchivo[32];

    if(pList != NULL)
    {
        utn_getTextoArchivo(rutaArchivo, "Ingrese la ruta del archivo a cargar (con extension): ", "Ingreso de caracteres invalido.\n", 32, 3);

        exit_status = controller_loadFromText(rutaArchivo, pList);
    }

    return exit_status;
}


/** \brief Listar pasajeros
 *
 * \param pList LinkedList* Puntero a LinkedList
 * \return int Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
 *
 */
int controller_listElements(LinkedList* pList)
{
	int exit_status = 0;
	eMovie* auxeMovie;

	if(pList != NULL)
	{
		// encabezado
		printHeader();
		for(int i=0; i<ll_len(pList); i++)
		{
			auxeMovie = (eMovie*) ll_get(pList, i);
			controller_printElement(auxeMovie);
		}
		exit_status = 1;
	}

    return exit_status;
}

/// @fn int controller_printElement(eMovie*)
/// @brief Imprime en pantalla los datos de un elemento
///
/// @param auxeMovie Puntero a eMovie
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int controller_printElement(eMovie* auxeMovie)
{
	int exit_status = 0;
	int id_peli;
	float rating;
	char titulo[32], genero[32];

	if(auxeMovie != NULL)
	{
		// getters
		eMovie_getId(auxeMovie, &id_peli);
		eMovie_getTitulo(auxeMovie, titulo);
		eMovie_getGenero(auxeMovie, genero);
		eMovie_getRating(auxeMovie, &rating);
		// print
		printf(" %4d   %-28s      %-20s       %.1f\n", id_peli, titulo, genero, rating);
		exit_status = 1;
	}

	return exit_status;
}


/** \brief Guarda los datos de la lista en el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo donde se guarda
 * \param pList LinkedList* Puntero a LinkedList
 * \return int Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
 *
 */
int controller_saveAsText(char* path , LinkedList* pList)
{
	int exit_status = 0;
	int len;
	eMovie* pAux = NULL;
	int id_peli;
	char titulo[32], genero[32];
	float rating;

	FILE* pFile = fopen(path, "w");

	if(pFile != NULL)
	{
	    printf("Escrbiendo en archivo de texto ...\n");
		//escribimos el encabezado
		fprintf(pFile, "id_peli,titulo,genero,rating\n");
		len = ll_len(pList);
		for(int i=0; i<len; i++)
		{
			pAux = ll_get(pList, i);
			eMovie_getId(pAux, &id_peli);
			eMovie_getTitulo(pAux, titulo);
			eMovie_getGenero(pAux, genero);
			eMovie_getRating(pAux, &rating);
			fprintf(pFile, "%d,%s,%s,%.1f\n", id_peli, titulo, genero, rating);

		}
		fclose(pFile);
        printf("Archivo guardado en '%s'\n\n", path);
		exit_status = 1;
	}
    return exit_status;
}

/** \brief Guarda los datos de la lista en el archivo data.csv (modo texto) pidiendo al usuario el nombre del archivo
 *
 * \param pList LinkedList* Puntero a LinkedList
 * \return int Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
 *
 */
int controller_saveAsText_userInput(LinkedList* pList)
{
    int exit_status = 0;
    char rutaArchivo[32];

    if(pList != NULL)
    {
        utn_getTextoArchivo(rutaArchivo, "Ingrese la ruta y nombre donde guardar el archivo (con extension): ", "Ingreso de caracteres invalido.\n", 32, 3);

        exit_status = controller_saveAsText(rutaArchivo, pList);
    }

    return exit_status;
}

/** \brief Mapea los valores de rating a una lista auxiliar, limpia la lista original y cambia el puntero a la lista mapeada
 *
 * \param pList LinkedList*
 * \return int Devuelve 1 si EXITO, 0 si ocurrio un error.
 *
 */
int controller_mapRandomRating(LinkedList* pList)
{
    int exit_status = 0;
    LinkedList* listaMapRating = NULL;

    if(pList != NULL)
    {
        // guardo la lista mapeada en un auxiliar
        listaMapRating = ll_map(pList, eMovie_mapRating);
        // clear a la lista a la que apunta pList
        ll_clear(pList);
        // pList apunta a la nueva LinkedList
        *pList = *listaMapRating;

        exit_status = 1;
    }

    return exit_status;
}

/** \brief Mapea los valores de genero a una lista auxiliar, limpia la lista original y cambia el puntero a la lista mapeada
 *
 * \param pList LinkedList*
 * \return int Devuelve 1 si EXITO, 0 si ocurrio un error.
 *
 */
int controller_mapRandomGenero(LinkedList* pList)
{
    int exit_status = 0;
    LinkedList* listaMapGenero = NULL;

    if(pList != NULL)
    {
        // guardo la lista mapeada en un auxiliar
        listaMapGenero = ll_map(pList, eMovie_mapGenero);
        // clear la lista a la que apunta pList
        ll_clear(pList);
        // pList apunta a la nueva LinkedList
        *pList = *listaMapGenero;

        exit_status = 1;
    }

    return exit_status;
}



