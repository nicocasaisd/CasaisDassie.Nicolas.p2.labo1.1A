#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "eMovie.h"


/// @fn int parser_eMovieFromText(FILE*, LinkedList*)
/// @brief Parsea los datos de los pasajeros desde el archivo data.csv (modo texto).
///
/// @param pFile Puntero a FILE
/// @param pList Puntero a LinkedList
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int parser_eMovieFromText(FILE* pFile , LinkedList* pList)
{
	int exit_status = 0;
	int r;
	char id_peli[50],titulo[50],genero[50],rating[50];
	eMovie* auxeMovie;

	if(pFile != NULL && pList != NULL)
	{
		// lectura fantasma del encabezado
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id_peli, titulo, genero, rating);

		while(!feof(pFile))
		{
			// guardo en variables auxiliares de tipo char
			r = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id_peli, titulo, genero, rating);
			// printf para testeo
//            printf("id:%s tit:%s gen:%s dur:%s \n", id_peli, titulo, genero, rating);
			if(r == 4)
			{
				// si fscanf pudo cargar todas las variables
				// cargo una variable con el constructor parametrizado
				auxeMovie = eMovie_newParametros(id_peli, titulo, genero, rating);
				if(auxeMovie != NULL)
				{
					// printf para testeo
//					printf("id:%d tit:%s gen:%s dur:%d \n", auxeMovie->id_peli, auxeMovie->titulo, auxeMovie->genero, auxeMovie->rating);

					//agrego el auxiliar eMovie cargado a la linkedlist
					ll_add(pList, auxeMovie);
					// seteo el auxiliar a NULL por seguridad
					auxeMovie = NULL;
					exit_status = 1;
				}
			}
			else
            {
                printf("Fallo en r fscanf\n");
            }
		}
	}
    return exit_status;
}

/// @fn int parser_eMovieFromBinary(FILE*, LinkedList*)
/// @brief  Parsea los datos de las peliculas desde el archivo data.bin (modo binario).
///
/// @param pFile Puntero a FILE
/// @param pList Puntero a LinkedList
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int parser_eMovieFromBinary(FILE* pFile , LinkedList* pList)
{
	int exit_status = 0;
	eMovie* auxeMovie;

	if(pFile != NULL && pList != NULL)
	{
		while(!feof(pFile))
		{
			// pido lugar para un eMovie en memoria dinamica
			auxeMovie = eMovie_new();
			if(auxeMovie != NULL)
			{
				// leo del archivo binario 1 eMovie y lo asigno a auxeMovie
				fread(auxeMovie, sizeof(eMovie), 1, pFile);
				// condicional para evitar lectura fantasma del archivo
				if(feof(pFile))
				{
					break;
				}
				//agrego el auxiliar eMovie cargado a la linkedlist
				ll_add(pList, auxeMovie);
				// seteo el auxiliar a NULL por seguridad
				auxeMovie = NULL;
				exit_status = 1;
			}
		}

	}
    return exit_status;
}
