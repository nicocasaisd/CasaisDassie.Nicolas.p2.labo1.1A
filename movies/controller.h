#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED



#endif // CONTROLLER_H_INCLUDED

// CARGA DE ARCHIVO
int controller_loadFromText(char* path , LinkedList* pList);
int controller_loadFromText_userInput(LinkedList* pList);

// LISTAR ELEMENTOS
int controller_listElements(LinkedList* pList);
int controller_printElement(eMovie* auxeMovie);


// GUARDAR ARCHIVO
int controller_saveAsText(char* path , LinkedList* pList);
int controller_saveAsText_userInput(LinkedList* pList);

// MAP
int controller_mapRandomRating(LinkedList* pList);
int controller_mapRandomGenero(LinkedList* pList);
