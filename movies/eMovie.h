#ifndef EMOVIE_H_INCLUDED
#define EMOVIE_H_INCLUDED

typedef struct{
    int id_peli;
    char titulo[32];
    char genero[32];
    float rating;
}eMovie;

#endif // EMOVIE_H_INCLUDED


// CONSTRUCTORES
eMovie* eMovie_new();
eMovie* eMovie_newParametros(char* id_peliStr,char* tituloStr,char* generoStr, char* duracionStr);

// DESTRUCTOR
void eMovie_delete(eMovie* movie);

// SETTERS
int eMovie_setId(eMovie* movie,int id_peli);
int eMovie_setTitulo(eMovie* movie,char* titulo);
int eMovie_setGenero(eMovie* movie,char* genero);
int eMovie_setRating(eMovie* movie,float rating);

//GETTERS
int eMovie_getTitulo(eMovie* movie,char* titulo);
int eMovie_getGenero(eMovie* movie,char* genero);
int eMovie_getRating(eMovie* movie,float* rating);
int eMovie_getId(eMovie* movie,int* id_peli);

// FILTRADORAS
int eMovie_filterByGeneroComedia(void* a);
int eMovie_filterByGeneroDrama(void* a);
int eMovie_filterByGeneroAccion(void* a);
int eMovie_filterByGeneroTerror(void* a);

// MAPEADORAS
void* eMovie_mapRating(void* pElement);
void* eMovie_mapGenero(void* pElement);

// COMPARADORAS
int eMovie_compareByGeneroYRating(void* a, void* b);
