/*
 * utn.c
 *
 *  Created on: 27 jun. 2022
 *      Author: nicocasaisd
 */
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#include "utn.h"



static int myGets(char* cadena, int longitud);

// getNumero
static int esNumerica(char* cadena);
static int getInt(int* pResultado);


//getNumeroConDecimales
static int esDecimal(char* cadena);
static int getFloat(float* pResultado);

//getTexto
static int getString(char* pResultado);
static int esTexto(char* cadena);

// getTextoAlfanumerico
static int getStringAlfa(char* pResultado);
static int esTextoAlfa(char* cadena);



/** \brief Lee del buffer de entrada y lo escribe en el puntero cadena
 *
 * \param cadena char* Vector de caracteres donde se escribe
 * \param longitud int  Cantidad de caracteres maximos
 * \return int Devuelve 0 si exito, -1 si ocurrio un error
 *
 */
static int myGets(char* cadena, int longitud)
{
    int retorno=-1;
    if(cadena != NULL && longitud > 0 && fgets(cadena, longitud, stdin) == cadena)
    {
        __fpurge(stdin);
        if(cadena[strlen(cadena)-1] == '\n')
        {
            cadena[strlen(cadena)-1] = '\0';
        }
        retorno = 0;
    }
    return retorno;
}

/**
* \brief ​ Verifica​ ​ si​ ​ la​ ​ cadena​ ​ ingresada​ ​ es​ ​ numerica
* \​param​ ​ cadena​ ​ Cadena​ ​ de​ ​ caracteres​ a ​ ser​ ​ analizada
* \return ​ Retorna​ 1 (​ verdadero​ ) ​ si​ ​ la​ ​ cadena​ ​ es​ ​ numerica​ y 0 (​ falso​ ) ​ si​ no ​ lo​ ​ es
*/
static int esNumerica(char* cadena)
{
    int i=0;
    int retorno = 1;
    if(cadena != NULL && strlen(cadena) > 0)
    {
        while(cadena[i] != '\0')
        {
            if(cadena[i] < '0' || cadena[i] > '9')
            {
                retorno = 0;
                break;
            }
            i++;
        }
    }

    return retorno;
}


/** \brief Obtiene una cadena del buffer, lo valida y convierte a entero
 *
 * \param pResultado int* Puntero al espacio de memoria donde se escribe
 * \return int Retorna 0 si se pudo obtener el numero entero y -1 si ocurrio un error.
 *
 */
static int getInt(int* pResultado)
{
    int ret = -1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer) && strlen(buffer)>0)
        {
            *pResultado = atoi(buffer);
            ret = 0;
        }
    }

    return ret;
}



/** \brief Pide al usuario que ingrese un dato. Si el ingreso es invalido lo informa y vuelve a pedir.
 *
 * \param int*  Puntero al espacio de memoria donde se escribe
 * \param char* Mensaje para pedir el ingreso
 * \param char* Mensaje de error por ingreso invalido
 * \param int Valor minimo del rango
 * \param int Valor maximo del rango
 * \param int Cantidad de reintentos posible
 * \return
 *
 */
int utn_getNumero(int* pResultado,
                  char* mensaje,
                  char* mensajeError,
                  int minimo,
                  int maximo,
                  int reintentos)
{
    int retorno;
    int bufferInt;

    while(reintentos > 0)
    {
        reintentos --;
        printf("%s", mensaje);
        if(getInt(&bufferInt) == 0)
        {
            if(bufferInt <= maximo && bufferInt >= minimo)
            {
                *pResultado = bufferInt;
                retorno = 0;
                break;
            }
        }
        printf("%s", mensajeError);
    }

    return retorno;
}

// GET NUMERO DECIMAL

/**
* \brief ​ Verifica​ ​ si​ ​ la​ ​ cadena​ ​ ingresada​ ​ es​ ​un numero decimal
* \​param​ ​ cadena​ ​ Cadena​ ​ de​ ​ caracteres​ a ​ ser​ ​ analizada
* \return ​ Retorna​ 1 (​ verdadero​ ) ​ si​ ​ la​ ​ cadena​ ​ es​ ​ decimal​ y 0 (​ falso​ ) ​ si​ no ​ lo​ ​ es
*/
static int esDecimal(char* cadena)
{
    int i=0;
    int retorno = 1;
    if(cadena != NULL && strlen(cadena) > 0)
    {
        while(cadena[i] != '\0')
        {
            if( (cadena[i] < '0' || cadena[i] > '9') && cadena[i]!= '.')
            {
                retorno = 0;
                break;
            }
            i++;
        }
    }

    return retorno;
}

/** \brief Obtiene una cadena del buffer, lo valida y convierte a flotante
 *
 * \param pResultado float* Puntero al espacio de memoria donde se escribe
 * \return int Retorna 0 si se pudo obtener el numero flotante y -1 si ocurrio un error.
 *
 */
static int getFloat(float* pResultado)
{
    int ret = -1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(myGets(buffer, sizeof(buffer)) == 0 && esDecimal(buffer))
        {
            *pResultado = atof(buffer);
            ret = 0;
        }
    }

    return ret;
}

/** \brief Pide al usuario que ingrese un dato. Si el ingreso es invalido lo informa y vuelve a pedir.
 *
 * \param float*  Puntero al espacio de memoria donde se escribe
 * \param char* Mensaje para pedir el ingreso
 * \param char* Mensaje de error por ingreso invalido
 * \param int Valor minimo del rango
 * \param int Valor maximo del rango
 * \param int Cantidad de reintentos posible
 * \return
 *
 */
int utn_getNumeroDecimal(float* pResultado,
                  char* mensaje,
                  char* mensajeError,
                  int minimo,
                  int maximo,
                  int reintentos)
{
    int retorno;
    float bufferFloat;

    while(reintentos > 0)
    {
        reintentos --;
        printf("%s", mensaje);
        if(getFloat(&bufferFloat) == 0)
        {
            if(bufferFloat <= maximo && bufferFloat >= minimo)
            {
                *pResultado = bufferFloat;
                retorno = 0;
                break;
            }
        }
        printf("%s", mensajeError);
    }

    return retorno;
}

// GET TEXTO

/**
* \brief ​ Verifica​ ​ si​ ​ la​ ​ cadena​ ​ ingresada​ ​ es​ ​ texto solo de caracteres alfabeticos
* \​param​ ​ cadena​ ​ Cadena​ ​ de​ ​ caracteres​ a ​ ser​ ​ analizada
* \return ​ Retorna​ 1 (​ verdadero​ ) ​ si​ ​ la​ ​ cadena​ ​ es​ ​ alfabetica​ y 0 (​ falso​ ) ​ si​ no ​ lo​ ​ es
*/
static int esTexto(char* cadena)
{
    int i=0;
    int retorno = 1;
    if(cadena != NULL && strlen(cadena) > 0)
    {
        while(cadena[i] != '\0')
        {
            if( ! ((cadena[i] >= 'A' && cadena[i] <= 'Z') || (cadena[i] >= 'a' && cadena[i] <= 'z')))
            {
                retorno = 0;
                break;
            }
            i++;
        }
    }

    return retorno;
}

/** \brief Obtiene una cadena del buffer, lo valida y copia al destino
 *
 * \param pResultado char* Puntero al espacio de memoria donde se escribe
 * \return int Retorna 0 si se pudo obtener la cadena y -1 si ocurrio un error.
 *
 */
static int getString(char* pResultado)
{
    int ret = -1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(myGets(buffer, sizeof(buffer)) == 0 && esTexto(buffer))
        {
            strcpy(pResultado, buffer);
            ret = 0;
        }
    }

    return ret;
}

/** \brief Pide al usuario que ingrese un dato. Si el ingreso es invalido lo informa y vuelve a pedir.
 *
 * \param char*  Puntero al espacio de memoria donde se escribe
 * \param char* Mensaje para pedir el ingreso
 * \param char* Mensaje de error por ingreso invalido
 * \param int Valor minimo del rango
 * \param int Valor maximo del rango
 * \param int Cantidad de reintentos posible
 * \return
 *
 */
int utn_getTexto(char* pResultado,
                  char* mensaje,
                  char* mensajeError,
                  int largo,
                  int reintentos)
{
    int retorno;
    char bufferStr[64];

    while(reintentos > 0)
    {
        reintentos --;
        printf("%s", mensaje);
        if(getString(bufferStr) == 0)
        {
            if(strlen(bufferStr) <= largo && strlen(bufferStr) > 0)
            {
                strcpy(pResultado, bufferStr);
                retorno = 0;
                break;
            }
        }
        printf("%s", mensajeError);
    }

    return retorno;
}


// GET TEXTO ALFANUMERICO

/**
* \brief ​ Verifica​ ​ si​ ​ la​ ​ cadena​ ​ ingresada​ ​ es​ ​ texto alfanumerico
* \​param​ ​ cadena​ ​ Cadena​ ​ de​ ​ caracteres​ a ​ ser​ ​ analizada
* \return ​ Retorna​ 1 (​ verdadero​ ) ​ si​ ​ la​ ​ cadena​ ​ es​ ​ alfanumerica​ y 0 (​ falso​ ) ​ si​ no ​ lo​ ​ es
*/
static int esTextoAlfa(char* cadena)
{
    int i=0;
    int retorno = 1;
    if(cadena != NULL && strlen(cadena) > 0)
    {
        while(cadena[i] != '\0')
        {
            if( ! ((cadena[i] >= 'A' && cadena[i] <= 'Z')
                   || (cadena[i] >= 'a' && cadena[i] <= 'z')
                   || (cadena[i] >= '0' && cadena[i] <= '9')
                   ))
            {
                retorno = 0;
                break;
            }
            i++;
        }
    }

    return retorno;
}

/** \brief Obtiene una cadena del buffer, lo valida y copia al destino
 *
 * \param pResultado char* Puntero al espacio de memoria donde se escribe
 * \return int Retorna 0 si se pudo obtener la cadena y -1 si ocurrio un error.
 *
 */
static int getStringAlfa(char* pResultado)
{
    int ret = -1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(myGets(buffer, sizeof(buffer)) == 0 && esTextoAlfa(buffer))
        {
            strcpy(pResultado, buffer);
            ret = 0;
        }
    }

    return ret;
}


/** \brief Pide al usuario que ingrese un dato. Si el ingreso es invalido lo informa y vuelve a pedir.
 *
 * \param char*  Puntero al espacio de memoria donde se escribe
 * \param char* Mensaje para pedir el ingreso
 * \param char* Mensaje de error por ingreso invalido
 * \param int Valor minimo del rango
 * \param int Valor maximo del rango
 * \param int Cantidad de reintentos posible
 * \return
 *
 */
int utn_getTextoAlfanumerico(char* pResultado,
                  char* mensaje,
                  char* mensajeError,
                  int largo,
                  int reintentos)
{
    int retorno;
    char bufferStr[64];

    while(reintentos > 0)
    {
        reintentos --;
        printf("%s", mensaje);
        if(getStringAlfa(bufferStr) == 0)
        {
            if(strlen(bufferStr) <= largo && strlen(bufferStr) > 0)
            {
                strcpy(pResultado, bufferStr);
                retorno = 0;
                break;
            }
        }
        printf("%s", mensajeError);
    }

    return retorno;
}

// GET TEXTO RUTA DE ARCHIVO

// GET TEXTO ALFANUMERICO

/**
* \brief ​ Verifica​ ​ si​ ​ la​ ​ cadena​ ​ ingresada​ ​ es​ ​ texto para usar en la ruta de archivo (alfanumerico y './_ '
* \​param​ ​ cadena​ ​ Cadena​ ​ de​ ​ caracteres​ a ​ ser​ ​ analizada
* \return ​ Retorna​ 1 (​ verdadero​ ) ​ si​ ​ la​ ​ cadena​ ​ es​ ​ valida​ y 0 (​ falso​ ) ​ si​ no ​ lo​ ​ es
*/
static int esTextoArchivo(char* cadena)
{
    int i=0;
    int retorno = 1;
    if(cadena != NULL && strlen(cadena) > 0)
    {
        while(cadena[i] != '\0')
        {
            if( ! ((cadena[i] >= 'A' && cadena[i] <= 'Z')
                   || (cadena[i] >= 'a' && cadena[i] <= 'z')
                   || (cadena[i] >= '-' && cadena[i] <= '9')
                   || (cadena[i] == ' ') || (cadena[i] == '_')
                   || (cadena[i] == '/')
                   ))
            {
                retorno = 0;
                break;
            }
            i++;
        }
    }

    return retorno;
}

/** \brief Obtiene una cadena del buffer, lo valida y copia al destino
 *
 * \param pResultado char* Puntero al espacio de memoria donde se escribe
 * \return int Retorna 0 si se pudo obtener la cadena y -1 si ocurrio un error.
 *
 */
static int getStringArchivo(char* pResultado)
{
    int ret = -1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(myGets(buffer, sizeof(buffer)) == 0 && esTextoArchivo(buffer))
        {
            strcpy(pResultado, buffer);
            ret = 0;
        }
    }

    return ret;
}

/** \brief Pide al usuario que ingrese un dato. Si el ingreso es invalido lo informa y vuelve a pedir.
 *
 * \param char*  Puntero al espacio de memoria donde se escribe
 * \param char* Mensaje para pedir el ingreso
 * \param char* Mensaje de error por ingreso invalido
 * \param int Valor minimo del rango
 * \param int Valor maximo del rango
 * \param int Cantidad de reintentos posible
 * \return
 *
 */
int utn_getTextoArchivo(char* pResultado,
                  char* mensaje,
                  char* mensajeError,
                  int largo,
                  int reintentos)
{
    int retorno;
    char bufferStr[64];

    while(reintentos > 0)
    {
        reintentos --;
        printf("%s", mensaje);
        if(getStringArchivo(bufferStr) == 0)
        {
            if(strlen(bufferStr) <= largo && strlen(bufferStr) > 0)
            {
                strcpy(pResultado, bufferStr);
                retorno = 0;
                break;
            }
        }
        printf("%s", mensajeError);
    }

    return retorno;
}

// VALIDACIONES

/// @fn int validarCadena(char[], int)
/// @brief Chequea que la cadena ingresada no exceda el largo máximo.
///
/// @param str Puntero a cadena
/// @param largo Numero entero maximo de caracteres permitidos
/// @return Devuelve 1 si la cadena es valida, 0 si la cadena es invalida
int validarCadena(char str[], int largo)
{
    int esValido = 0;
    if(str != NULL && strlen(str) < largo)
    {
        esValido = 1;
    }
    return esValido;
}

// PAUSAR

/// @fn void pausar()
/// @brief Pausa la consola hasta que se presione la tecla enter.
///
void pausar()
{
    char auxPausa;
    __fpurge(stdin);
    printf("\n\nPresione enter para continuar...");
    scanf("%c", &auxPausa);
}
