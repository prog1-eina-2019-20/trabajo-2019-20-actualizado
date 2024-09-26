/******************************************************************************\
 * Curso de Programación 1. Trabajo obligatorio curso 2019-20
 * Autor: Miguel Ángel Latre Abadía
 * Última revisión: 25-10-2021
 * Resumen: Fichero de interfaz «diccionario» de un módulo que declara
 *          una función denominada «contarPalabras» que, dado un fichero de
 *          texto, cuenta el número de palabras que aparecen y que no aparecen
 *          en un diccionario almacenado en el fichero «FICH_DICCIONARIO». 
 * Codificación de caracteres original de este fichero: UTF-8 sin BOM
\******************************************************************************/
#include <string>
using namespace std;
#pragma once

/*
 * Ruta de acceso y nombre del fichero diccionario que contiene una lista de
 * palabras en español, en minúsculas, a razón de una por línea y, por
 * limitaciones para trabajar con UTF-8 en C++ y con los compiladores
 * utilizados, sin eñes ni diacríticos.
 */
const string FICH_DICCIONARIO = "datos/diccionario.dic";


/*
 * Pre:  «nombreFichero» es una cadena de caracteres cuyo valor representa el
 *       nombre de un fichero de texto que utiliza la misma codificación de
 *       caracteres que el fichero «FICH_DICCIONARIO». Los valores de los
 *       parámetros «encontradas» y «noEncontradas» no están definidos.
 * Post: Ha asignado a los parámetros «encontradas» y «noEncontradas» el
 *       número de palabras contenidas en el fichero de nombre
 *       «nombreFichero» que, respectivamente, se encuentran y no se han
 *       encontrado en el diccionario almacenado en «FICH_DICCIONARIO». Ha
 *       devuelto «true» cuando el fichero de nombre «nombreFichero» ha podido
 *       procesarse correctamente, y «false» en caso contrario.
 */
bool contarPalabras(const string nombreFichero,
                    unsigned &encontradas, unsigned &noEncontradas);
