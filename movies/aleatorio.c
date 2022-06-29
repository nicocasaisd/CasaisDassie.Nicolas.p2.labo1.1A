#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "aleatorio.h"




/** \brief Devuelve un numero aleatorio en un rango
 *
 * \param min int Minimo del rango
 * \param max int Maximo del rango
 * \return int Numero entero aleatorio
 *
 */
int randomRangeInt(int min, int max)
{
    int valor;
    valor = (rand() % (max - min + 1) + min);

    return valor;
}

/** \brief Devuelve un numero aleatorio en un rango con decimales
 *
 * \param min int Minimo del rango
 * \param max int Maximo del rango
 * \param decimales int Cantidad de valores decimales
 * \return float Numero flotante aleatorio
 *
 */
float randomRangeFloat(int min, int max, int decimales)
{
    float valor;
    int magnitud = pow(10, decimales);
    // si no reconoce la lib <math.h> hacer:
    //  Settings -> Compiler -> Linker settings (tab) -> other linker options -> -lm

    min *= magnitud;
    max *= magnitud;

    valor = (float) (rand() % (max - min + 1) + min) / magnitud;

    return valor;
}
