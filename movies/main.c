#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "aleatorio.h"
#include "LinkedList.h"
#include "eMovie.h"
#include "parser.h"
#include "controller.h"
#include "menu.h"
#include "utn.h"

int main()
{
    // semilla rand
    srand(time(NULL));

    LinkedList* lista = ll_newLinkedList();

    LinkedList* listaFilterComedia = NULL;
    LinkedList* listaFilterDrama = NULL;
    LinkedList* listaFilterAccion = NULL;
    LinkedList* listaFilterTerror = NULL;

//
//    LinkedList* listaMapRating = NULL;
//    LinkedList* listaMapGenero = NULL;


    char salir = 'n';
    char salirMenuFiltro = 'n';

    // chequeo que se haya creado la lista
    if(lista == NULL)
    {
        printf("No se consiguio memoria \n");
        exit(1);
    }


    do
    {
        system("clear");
        switch(menu())
        {
        case 1:
            // CARGAR
            controller_loadFromText_userInput(lista);
            break;
        case 2:
            //LISTAR
            controller_listElements(lista);
            printf("\ncantidad de elementos en memoria: %d\n", ll_len(lista));
            break;
        case 3:
            //MAPEAR
            controller_mapRandomRating(lista);
            if(lista == NULL)
            {
                printf("Ocurrio un error al mapear el rating");
            }
            controller_listElements(lista);
            break;
        case 4:
            //MAPEAR
            controller_mapRandomGenero(lista);
            if(lista == NULL)
            {
                printf("Ocurrio un error al mapear el genero");
            }
            controller_listElements(lista);
            break;
        case 5:
            // FILTRAR
            do
            {
                switch(menuFiltrado())
                {
                case 1:
                    listaFilterComedia = ll_filter(lista, eMovie_filterByGeneroComedia);
                    controller_saveAsText("movies_comedia.csv", listaFilterComedia);
                    //controller_listElements(listaFilterComedia);
                    break;
                case 2:
                    listaFilterDrama = ll_filter(lista, eMovie_filterByGeneroDrama);
                    controller_saveAsText("movies_drama.csv", listaFilterDrama);
                    //controller_listElements(listaFilterDrama);
                    break;
                case 3:
                    listaFilterAccion = ll_filter(lista, eMovie_filterByGeneroAccion);
                    controller_saveAsText("movies_accion.csv", listaFilterAccion);
                    //controller_listElements(listaFilterAccion);
                    break;
                case 4:
                    listaFilterTerror = ll_filter(lista, eMovie_filterByGeneroTerror);
                    controller_saveAsText("movies_terror.csv", listaFilterTerror);
                    //controller_listElements(listaFilterTerror);
                    break;
                case 5:
                    salirMenuFiltro = 's';
                    break;
                }
            }
            while(salirMenuFiltro != 's');

            break;
        case 6:
            // ORDENAR
            ll_sort(lista, eMovie_compareByGeneroYRating, 0);
            printf("\n\t*** Listado de peliculas por genero y rating descendente ***\n\n");
            controller_listElements(lista);
            break;
        case 7:
            // GUARDAR
            controller_saveAsText_userInput(lista);
            break;
        case 8:
            salir = 's';
            break;
        }
        pausar();
    }
    while(salir != 's');



    // elimino las listas
    ll_deleteLinkedList(lista);
    ll_deleteLinkedList(listaFilterComedia);
    ll_deleteLinkedList(listaFilterDrama);
    ll_deleteLinkedList(listaFilterAccion);
    ll_deleteLinkedList(listaFilterTerror);

    printf("Listas en memoria eliminadas..");

    return 0;
}
