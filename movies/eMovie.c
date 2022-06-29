#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eMovie.h"
#include "utn.h"
#include "aleatorio.h"




/****************************************************
            CONSTRUCTORES Y DESTRUCTOR
*****************************************************/

/// @fn eMovie eMovie_new*()
/// @brief Crea una estructura eMovie en memoria dinamica y devuelve un puntero hacia ella
///
/// @return
eMovie* eMovie_new()
{
	eMovie* new_eMovie = (eMovie*) calloc(1, sizeof(eMovie));

	return new_eMovie;
}

/// @fn eMovie eMovie_newParametros(char*, char*, char*, char*)
/// @brief Crea una estructura eMovie en memoria dinamica y devuelve un puntero hacia ella a partir de todos sus campos como parametros tipo string
///
/// @param idStr
/// @param nombreStr
/// @param apellidoStr
/// @param precioStr
/// @param tipoPasajeroStr
/// @param codigoVueloStr
/// @param statusFlightStr
/// @return
eMovie* eMovie_newParametros(char* id_peliStr,char* tituloStr,char* generoStr, char* ratingStr)
{
	// pido memoria para un eMovie
	eMovie* new_eMovie = eMovie_new();
	// valido
	if(new_eMovie != NULL)
	{
		if(!(	eMovie_setId(new_eMovie, atoi(id_peliStr)) &&
				eMovie_setTitulo(new_eMovie, tituloStr) &&
				eMovie_setGenero(new_eMovie, generoStr) &&
				eMovie_setRating(new_eMovie, atof(ratingStr))
				))
		{
		    // si falla la carga se borra la nueva estructura
			eMovie_delete(new_eMovie);
			new_eMovie = NULL;
		}
	}
	return new_eMovie;
}


/// @fn void eMovie_delete(eMovie*)
/// @brief Libera en memoria a la estructura eMovie
///
/// @param movie Puntero a eMovie a borrar
void eMovie_delete(eMovie* movie)
{
	if(movie != NULL)
	{
		free(movie);
	}

}

/****************************************************
                    SETTERS
*****************************************************/

/// @fn int eMovie_setId(eMovie*, int)
/// @brief Valida y asigna la id a la estructura eMovie
///
/// @param movie Puntero a eMovie
/// @param id
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int eMovie_setId(eMovie* movie,int id_peli)
{
	int exit_status = 0;
	if(movie != NULL && id_peli > 0)
	{
		movie->id_peli = id_peli;
		exit_status = 1;
	}

	return exit_status;
}

/// @fn int eMovie_setTitulo(eMovie*, char*)
/// @brief Valida y asigna el nombre a la estructura eMovie
///
/// @param movie Puntero a eMovie
/// @param titulo Vector de caracteres
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int eMovie_setTitulo(eMovie* movie,char* titulo)
{
	int exit_status = 0;
	if(movie != NULL && titulo != NULL)
	{
		if(validarCadena(titulo, 50))
		{
			strncpy(movie->titulo, titulo, sizeof(movie->titulo));
			exit_status = 1;
		}
	}

	return exit_status;
}


/// @fn int eMovie_setGenero(eMovie*, char*)
/// @brief Valida y asigna el nombre a la estructura eMovie
///
/// @param movie Puntero a eMovie
/// @param genero Vector de caracteres
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int eMovie_setGenero(eMovie* movie,char* genero)
{
	int exit_status = 0;
	if(movie != NULL && genero != NULL)
	{
		if(validarCadena(genero, 50))
		{
			strncpy(movie->genero, genero, sizeof(movie->genero));
			exit_status = 1;
		}
	}

	return exit_status;
}

/// @fn int eMovie_setRating(eMovie*, int)
/// @brief Valida y asigna la id a la estructura eMovie
///
/// @param movie Puntero a eMovie
/// @param rating
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int eMovie_setRating(eMovie* movie,float rating)
{
	int exit_status = 0;
	if(movie != NULL && rating > -1)
	{
		movie->rating = rating;
		exit_status = 1;
	}

	return exit_status;
}

/****************************************************
                    GETTERS
*****************************************************/

/// @fn int eMovie_getId(eMovie*, int*)
/// @brief Obtiene la id de la estructura y la asigna en el valor del puntero int
///
/// @param movie Puntero a eMovie
/// @param id_peli Puntero a int de la id_peli
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int eMovie_getId(eMovie* movie,int* id_peli)
{
	int exit_status = 0;
		if(movie != NULL && id_peli != NULL)
		{
			*id_peli = movie->id_peli;
			exit_status = 1;
		}

	return exit_status;
}


/// @fn int eMovie_getRating(eMovie*, int*)
/// @brief Obtiene la id de la estructura y la asigna en el valor del puntero int
///
/// @param movie Puntero a eMovie
/// @param duracion Puntero a int de la duracion
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int eMovie_getRating(eMovie* movie,float* rating)
{
	int exit_status = 0;
		if(movie != NULL && rating != NULL)
		{
			*rating = movie->rating;
			exit_status = 1;
		}

	return exit_status;
}

/// @fn int eMovie_getTitulo(eMovie*, char*)
/// @brief Obtiene la titulo de la estructura y la asigna en el valor del puntero char
///
/// @param movie Puntero a eMovie
/// @param titulo Vector de caracteres
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int eMovie_getTitulo(eMovie* movie,char* titulo)
{
	int exit_status = 0;
		if(movie != NULL && titulo != NULL)
		{
			strcpy(titulo, movie->titulo);
			exit_status = 1;
		}

	return exit_status;
}

/// @fn int eMovie_getGenero(eMovie*, char*)
/// @brief Obtiene la titulo de la estructura y la asigna en el valor del puntero char
///
/// @param movie Puntero a eMovie
/// @param genero Vector de caracteres
/// @return Devuelve 0 si ocurrio un error, y 1 si se completo exitosamente.
int eMovie_getGenero(eMovie* movie,char* genero)
{
	int exit_status = 0;
		if(movie != NULL && genero != NULL)
		{
			strcpy(genero, movie->genero);
			exit_status = 1;
		}

	return exit_status;
}


/****************************************************
                    FILTRADORAS
*****************************************************/

int eMovie_filterByGeneroComedia(void* a)
{
    int condicion = 0;
    eMovie* auxpMovie = NULL;
    char genero[32];

    if(a != NULL)
    {
        // casteo
        auxpMovie = (eMovie*) a;
        // get genero
        eMovie_getGenero(auxpMovie, genero);
        // condicion
        if(strcmp(genero, "comedia") == 0)
        {
            condicion = 1;
        }
    }

    return condicion;
}

int eMovie_filterByGeneroDrama(void* a)
{
    int condicion = 0;
    eMovie* auxpMovie = NULL;
    char genero[32];

    if(a != NULL)
    {
        // casteo
        auxpMovie = (eMovie*) a;
        // get genero
        eMovie_getGenero(auxpMovie, genero);
        // condicion
        if(strcmp(genero, "drama") == 0)
        {
            condicion = 1;
        }
    }

    return condicion;
}

int eMovie_filterByGeneroAccion(void* a)
{
    int condicion = 0;
    eMovie* auxpMovie = NULL;
    char genero[32];

    if(a != NULL)
    {
        // casteo
        auxpMovie = (eMovie*) a;
        // get genero
        eMovie_getGenero(auxpMovie, genero);
        // condicion
        if(strcmp(genero, "accion") == 0)
        {
            condicion = 1;
        }
    }

    return condicion;
}

int eMovie_filterByGeneroTerror(void* a)
{
    int condicion = 0;
    eMovie* auxpMovie = NULL;
    char genero[32];

    if(a != NULL)
    {
        // casteo
        auxpMovie = (eMovie*) a;
        // get genero
        eMovie_getGenero(auxpMovie, genero);
        // condicion
        if(strcmp(genero, "terror") == 0)
        {
            condicion = 1;
        }
    }

    return condicion;
}



/****************************************************
                    MAPEADORAS
*****************************************************/

void* eMovie_mapRating(void* pElement)
{
    void* pRetorno = NULL;
    eMovie* auxpElement;
    float rating;

    if(pElement != NULL)
    {
        rating = randomRangeFloat(1, 10, 1);
        // casteo a eMovie
        auxpElement = (eMovie*) pElement;
        // set rating
        eMovie_setRating(auxpElement, rating);

        // casteo a void
        pRetorno = (void*) auxpElement;

    }

    return pRetorno;
}

void* eMovie_mapGenero(void* pElement)
{
    void* pRetorno = NULL;
    eMovie* auxpElement;
    int aleatorio;
    char genero[4][32] = {
                            {"drama"},
                            {"comedia"},
                            {"accion"},
                            {"terror"}
                            };

    if(pElement != NULL)
    {
        aleatorio = randomRangeInt(0, 3);
        printf("%d\n", aleatorio);
        // casteo a eMovie
        auxpElement = (eMovie*) pElement;
        // set genero
        eMovie_setGenero(auxpElement, genero[aleatorio]);

        // casteo a void
        pRetorno = (void*) auxpElement;

    }

    return pRetorno;
}


/****************************************************
                    COMPARADORAS
*****************************************************/

int eMovie_compareByGeneroYRating(void* a, void* b)
{
	int comparison = 0;
	char genero1[32], genero2[32];
	float rating1, rating2;
	eMovie* first;
	eMovie* second;

	if(a != NULL && b != NULL)
	{
		// casteo a eMovie
		first = (eMovie*) a;
		second = (eMovie*) b;
		// cargo generos
		eMovie_getGenero(first, genero1);
		eMovie_getGenero(second, genero2);

		// cargo rating
		eMovie_getRating(first, &rating1);
		eMovie_getRating(second, &rating2);
		//printf("gen1:%s    gen2:%s    dur1:%d    dur2:%d\n", genero1, genero2, rating1, rating2);
		// comparacion de strings
		comparison = strcmp(genero1, genero2);
		if(comparison > 0)
		{
			comparison = 1;
		}
		else if(comparison < 0)
		{
			comparison = -1;
		}
		else // si son iguales
        {
            if(rating1 > rating2)
            {
                comparison = 1;
            }
            else if(rating1 < rating2)
            {
                comparison = -1;
            }
        }
	}
    return comparison;
}
