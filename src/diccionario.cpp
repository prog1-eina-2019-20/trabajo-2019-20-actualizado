/******************************************************************************\
 * Curso de Programación 1. Trabajo obligatorio curso 2019-20
 * Autor: Miguel Ángel Latre Abadía
 * Última revisión: 25-10-2021
 * Resumen: Fichero de implementación «diccionario.cpp» de un módulo que 
 *          define una función denominada «contarPalabras» que, dado un
 *          fichero de texto, cuenta el número de palabras que aparecen y que
 *          no aparecen en un diccionario almacenado en el fichero
 *          «FICH_DICCIONARIO». 
 * Codificación de caracteres original de este fichero: UTF-8 sin BOM
\******************************************************************************/

#include <iostream>
#include <fstream>
#include "diccionario.hpp"
using namespace std;

/*
 * Número máximo de palabras que puede haber en el diccionario
 */
const unsigned MAX_PALABRAS = 170000;

struct Diccionario {
    string palabras[MAX_PALABRAS];
    unsigned numPalabras = 0;
    bool cargado = false;
};


/*
 * Pre:  «palabra» es una cadena de caracteres que no contiene ningún carácter
         blanco (ni espacios en blanco, tabulaciones o caracteres de cambio de
         línea).
 * Post: Cuando se ha terminado de ejecutar esta función, la cadena de
 *       caracteres «palabra» contiene únicamente las letras del alfabeto
 *       inglés que contenía inicialmente (cuando se comenzó a ejecutar esta
 *       función), en minúsculas. Cualquier otro carácter ha sido eliminado.
 *
 *       Ejemplos:
 *
 *       Valor inicial de «palabra»         Valor final de «palabra»
 *       -----------------------------------------------------------
 *       ""                                 ""
 *       "En"                               "en"
 *       "un"                               "un"
 *       "Mancha,"                          "mancha"
 *       "corredor."                        "corredor"
 *       "-¡Oh!"                            "oh"
 *       "¿Duermen?"                        "duermen"
 *       "1604"                             ""
 *       "H2SO4"                            "hso"
 */
void limpiar(string& palabra) {
    // Índice con el que escribir cada carácter del valor final de «palabra».
    // Se va a incrementar en 1 o 0 componentes por iteración, dependiendo de
    // si palabra.at(i) es una letra o no. Por ello, se va a cumplir
    // que indLimpia <= i.
    int indLimpia = 0;

    for (unsigned i = 0; i < palabra.length(); i++) {
        if (isalpha(palabra.at(i))) {
            palabra.at(indLimpia) = tolower(palabra.at(i));
            indLimpia++;
        }
    }

    // Como indLimpia <= i, hay que asegurarse de que la palabra
    // limpia tiene «indLimpia» caracteres.
    palabra.resize(indLimpia);
}


/*
 * Pre:  Existe un fichero de texto denominado «FICH_DICCIONARIO» que contiene
 *       una única palabra por línea, escrita exclusivamente en minúsculas.
 *       Las palabras del mismo están ordenadas alfabéticamente de forma
 *       ascendente. En el fichero no hay más de «MAX_PALABRAS». El vector 
 *       «dicc.palabras» tiene al menos «MAX_PALABRAS» componentes.
 * Post: Ha asignado al campo «numPalabras» del parámetro «dicc» el número de
 *       palabras que contiene el fichero «FICH_DICCIONARIO», y a las
 *       «dicc.numPalabras» primeras componentes del vector «dicc.palabras», las
 *       palabras contenidas en el fichero, en el mismo orden en que aparecen en
 *       este (por tanto, ordenadas alfabéticamente). Ha devuelto «true» si el
 *       fichero «nombreFichero» se ha podido leer, y «false» en caso contrario.
 */
bool cargarDiccionario(Diccionario& dicc) {
    ifstream f(FICH_DICCIONARIO);
    if (f.is_open()) {
        dicc.numPalabras = 0;
        while (getline(f, dicc.palabras[dicc.numPalabras]) 
               && dicc.numPalabras < MAX_PALABRAS - 1) {
        // Mientras se leen los datos del flujo y la última lectura es correcta
            // Se procesa el último dato leído: 
            dicc.numPalabras++;
        }
        f.close();
        dicc.cargado = true;
        return true;
    }
    else {
        cerr << "No se ha podido abrir el fichero \"" << FICH_DICCIONARIO
             << "\"." << endl;
        return false;
    }
}


/*
 * Pre:  numPalabras > 0;
 *       el vector «dicc» tiene al menos «numPalabras» componentes;
 *       las «numPalabras» primeras componentes del vector «dicc» están
 *       ordenadas alfabéticamente de forma ascendente.
 * Post: Si entre las cadenas de caracteres del vector «dicc» hay una
 *       igual al valor del parámetro «palabra», ha devuelto el índice de
 *       dicha cadena en el vector; en caso contrario, ha devuelto un valor
 *       negativo.
 */
int buscar(const string palabra, const Diccionario& dicc) {
    unsigned inf = 0;
    unsigned sup = dicc.numPalabras - 1;
    while (inf < sup) {
        unsigned med = (inf + sup) / 2;
        if (palabra > dicc.palabras[med]) {
            inf = med + 1;
        }
        else {
            sup = med;
        }
    }

    if (palabra == dicc.palabras[inf]) {
        return inf;
    }
    else {    
        return -1;
    }
}


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
                    unsigned& encontradas, unsigned& noEncontradas) {
    static Diccionario dicc;
    if (!dicc.cargado) {
        if (!cargarDiccionario(dicc)) {
            return false;
        }
    }
    ifstream texto(nombreFichero);
    if (texto.is_open()) {
        encontradas = 0;
        noEncontradas = 0;
        string palabra;

        // Lectura con el operador de extracción, puesto que hay dos
        // delimitadores de «palabras» válidos: ' ' y '\n' («getline» solo
        // permite especificar un delimitador, por lo que no es útil en este
        // caso).
        while (texto >> palabra) {
        // Mientras se leen los datos del flujo y la última lectura es correcta
            // Se procesa la última «palabra» leída:
            limpiar(palabra);
            if (buscar(palabra, dicc) >= 0) {
                // El índice devuelto corresponde a una componente válida del
                // vector: «palabra» se ha encontrado en el diccionario.
                encontradas++;
            }
            else {
                // Se ha devuelto -1: «palabra» no está en el diccionario.
                noEncontradas++;
            }
        }
        texto.close();
        return true;
    }
    else {
        return false;
    }
}
