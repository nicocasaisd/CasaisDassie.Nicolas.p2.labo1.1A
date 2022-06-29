#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "eMovie.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;

    this = (LinkedList*) malloc(sizeof(LinkedList));

    if(this != NULL)
    {
    	this->size = 0;
    	this->pFirstNode = NULL;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	returnAux = this->size;
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	// obtiene la dir de memoria del vagon en ese indice
	Node* pNode = NULL;

	if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
	{
		pNode = this->pFirstNode;
		for(int i=0; i<nodeIndex;i++)
		{
			pNode = pNode->pNextNode;
		}
	}

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* newNode = NULL;
    Node* previousNode = NULL;

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
    	// malloc de nodo
    	newNode = (Node*) malloc(sizeof(Node));
    	if(newNode != NULL)
    	{
    		 //asigno el pElement de newNode al que recibi por parametro
			newNode->pElement = pElement;
			if(nodeIndex == 0)
			{
				// el nuevo apunta al nodo que apuntaba la LL
				newNode->pNextNode = this->pFirstNode;
				// la LL apunta al nuevo nodo
				this->pFirstNode = newNode;
			}
			else
			{
				// obtengo el nodo previo
				previousNode = getNode(this, nodeIndex-1);
				// el nuevo nodo apunta al del indice siguiente
				newNode->pNextNode = previousNode->pNextNode;
				// el nodo previo apunta al nuevo nodo
				previousNode->pNextNode = newNode;

			}
			// aumento el size de la LL
			this->size += 1;
			returnAux = 0;
    	}
    }
    // pElement
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	return addNode(this, ll_len(this), pElement);
}

/** \brief Retorna un puntero al elemento que se encuentra en el índice especificado.
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxpNode = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	// obtengo el puntero al nodo en el indice solicitado
    	auxpNode = getNode(this, index);
    	// asigno la direccion del elemento de ese nodo a returnAux
    	returnAux = auxpNode->pElement;
    }

    return returnAux;
}


/** \brief Asigna un elemento al Nodo en el índice especificado en la LinkedList
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pNode = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	// obtengo el puntero al Nodo
    	pNode = getNode(this, index);
    	// asigno pElement al campo del Nodo
    	pNode->pElement = pElement;

    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pPreviousNode;
    Node* pNextNode;
    Node* pRemovedNode;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	pRemovedNode = getNode(this, index);
    	if(index == 0)
    	{
        	// obtengo el nodo siguiente del que quiero eliminar
        	//pNextNode = getNode(this, index+1);
        	 pNextNode = pRemovedNode->pNextNode;
        	// el pFirstNode de la LinkedList ahora apunta al siguiente
        	this->pFirstNode = pNextNode;
    	}
    	else
    	{
        	// obtengo el nodo previo y el siguiente del que quiero eliminar
        	pPreviousNode = getNode(this, index-1);
        	// si el nodo es el ultimo, el indice fuera de rango devuelve NULL asi que esta bien
        	//pNextNode = getNode(this, index+1);
        	pNextNode = pRemovedNode->pNextNode;
        	// el previo ahora apunta al siguiente
        	pPreviousNode->pNextNode = pNextNode;
    	}
    	// hago un free del nodo a eliminar
		free(pRemovedNode);
		// modifico el size de la LinkedList
		this->size -= 1;
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	// mientras el size de la LL sea mayor a 0, borrar el elemento 0
    	while(ll_len(this)>0)
    	{
    		ll_remove(this, 0);
    	}
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	// hago clear de los Nodos de la LL
    	ll_clear(this);
    	// elimino la estructura LinkedList
		free(this);

		returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    Node* auxpElement = NULL;
    if(this != NULL)
    {
    	// itero sobre todos los elementos de la LL
    	for(int i=0; i<len; i++)
    	{
    		// obtengo el puntero del elemento en el indice i
    		//auxpNode = getNode(this, i);
    		auxpElement = ll_get(this, i);
    		// me fijo si pElement coincide
    		if(auxpElement == pElement)
    		{
    			// devuelvo el indice i y break
    			returnAux = i;
    			break;
    		}
    	}
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(getNode(this, 0) == NULL)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief Inserta un nuevo Nodo en la lista en la posicion indicada, le asigna el elemento y desplaza a los demas nodos.
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
	// no validamos porque ya valida addNode (es la misma funcion)
	return addNode(this, index, pElement);

}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	returnAux = ll_get(this, index);
    	ll_remove(this, index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	// operador ternario
    	returnAux = ll_indexOf(this, pElement) != -1 ? 1: 0;
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* pAuxElement = NULL;
    int len;

	if(this != NULL && this2 != NULL)
	{
		// asigno returnAux a 1 suponiendo que todos los elementos estan contenidos
		returnAux = 1;
		len = ll_len(this2);
		// itero sobre los elementos de this2
		for(int i=0; i<len; i++)
		{
			// obtengo el pElement del indice i de this2
			pAuxElement = ll_get(this2, i);
			// pregunto si el elemento NO esta en la lista this
			if(ll_contains(this, pAuxElement) == 0)
			{
				returnAux = 0;
				break;
			}
		}
	}

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pAuxElement = NULL;

    if(this != NULL && from >= 0 && from < ll_len(this) && to > from && to <= ll_len(this))
    {
    	// creo una nueva LinkedList
    	cloneArray = ll_newLinkedList();
    	// itero sobre los elementos entre from y to (no incluido)
    	for(int i = from; i<to; i++)
    	{
    		// obtengo el elemento en el indice i
    		pAuxElement = ll_get(this, i);
    		// agrego el Nodo a la lista clonada y le asigno el elemento del indice i
    		ll_add(cloneArray, pAuxElement);
    	}

    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL)
    {
    	// clono la LL desde 0 hasta el size
    	// incluye al ultimo porque ll_subList permite copiar hasta un indice igual al size de la lista
    	cloneArray = ll_subList(this, 0, ll_len(this));
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int len;
    void* pElementI = NULL;
    void* pElementJ = NULL;

    if(this != NULL && pFunc != NULL && (order == 1 || order == 0))
    {
    	len = ll_len(this);
    	// burbujeo
    	for(int i=0; i<len-1; i++)
    	{
    		for(int j=i+1; j<len; j++)
    		{
    			// asignos elementos I y J
    			pElementJ = ll_get(this, j);
				pElementI = ll_get(this, i);
					// (en cada iteracion de J tengo que volver a pedir valores
					// porque el swap los puede cambiar)
    			// comparacion entre elementos de I y J
    			if((order == 1 && pFunc(pElementI, pElementJ) == 1)
    			|| (order == 0 && pFunc(pElementI, pElementJ) == -1))
    			{
    				// swap
    				ll_set(this, i, pElementJ);
    				ll_set(this, j, pElementI);
    			}

    		}
    	}
    	returnAux = 0;
    }

    return returnAux;

}


/// @fn LinkedList ll_filter*(LinkedList*, int(*)(void*))
/// @brief Filtra los elementos del LinkedList
///
/// @param this LinkedList
/// @param pFunc puntero a la funcion filtrante
/// @return Devuelve una nueva LinkedList con los elementos filtrados o NULL si hubo un error
LinkedList* ll_filter(LinkedList* this, int (*pFunc) (void*))
{
	LinkedList* filterList = NULL;
	void* auxpElement = NULL;
	int len;

	if(this != NULL && pFunc != NULL)
	{
		// creo una nueva LinkedList
		filterList = ll_newLinkedList();
		if(filterList != NULL)
		{
			len = ll_len(this);
			// itero
			for(int i=0; i<len; i++)
			{
				// guardo el elemento en aux
				auxpElement = ll_get(this, i);
				// pregunto
				if(pFunc(auxpElement))
				{
					// agrego a filterList
					ll_add(filterList, auxpElement);
				}
			}
		}
	}
	return filterList;
}



/** \brief Mapea los valores de una lista y los devuelve en una nueva lista.
 *
 * \param LinkedList* this LinkedList
 * \param pFunc puntero a la funcion que mapea valores
 * \return Devuelve una nueva LinkedList con los elementos filtrados o NULL si hubo un error.
 *
 */
LinkedList* ll_map(LinkedList* this, void*(*pFunc)(void*))
{
    LinkedList* mapList = NULL;
    void* auxpMap = NULL;
    int len;

    if(this != NULL && pFunc != NULL)
    {
        // creo una nueva LinkedList
		mapList = ll_newLinkedList();
		if(mapList != NULL)
		{
			len = ll_len(this);
			// itero
			for(int i=0; i<len; i++)
			{
				// mapeo
                auxpMap = pFunc(ll_get(this, i));
                // agrego a mapList
                if(auxpMap != NULL)
                {
                    ll_add(mapList, auxpMap);
                }
			}
		}
    }
    return mapList;
}









