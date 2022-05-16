/** @file mapa_categorias.hh
    @brief Especificación de la clase mCategorias
*/

#ifndef MAPA_CATEGORIAS_HH
#define MAPA_CATEGORIAS_HH

#ifndef NO_DIAGRAM
#include <map>
#include <vector>
#include <iostream>
using namespace std;
#endif

/** @class mCategorias
    @brief Representa un conjunto de todas las categorias del circuito
*/
class mCategorias {
    private:

        map<string,vector<int>> categorias;
        vector<string> nombres;
        int size;
        int maxpuntos;

    public:

        // Creadoras
        
        /** @brief Creadora definida
                
            \pre <em>cierto</em>
            \post Se ha creado una lista de c categorías y k niveles máximos
        */
        mCategorias(int c, int k);
        
        // Modificadoras
        
        /** @brief Operación de lectura
                
            \pre En el canal estándar de entrada hay tantos nombres como categorías declaradas, seguidos
            de tantas listas como categorías hay, donde cada una tiene tantos valores como niveles hay
            \post Se han leído todas las categorías que cabían en el conjunto
        */
        void leer();
        
        // Consultoras
        
        /** @brief Operación de escritura de categorías
                
            \pre <em>cierto</em>
            \post Se han escrito todos nombres de las categorías en el canal estándar de salida,
            por orden creciente de identificador, además de la tabla de niveles en orden creciente
            de nivel
        */
        void escribir() const;

        /** @brief Consultora de nombre

            \pre <em>cierto</em>
            \post Se devuelve el nombre de la categoría de identificador id
        */
        string consultar_nombre(int id) const;

        /** @brief Consultora de puntos
                
            \pre id corresponde al identificador de una categoría válida, y n a una posición puntuable
            de la categoría
            \post Se devuelve la cantidad de puntos que corresponden a la posición n en la categoría
            de identificador id
        */
        int consultar_puntos(int id, int n) const;

        /** @brief Consultora de cantidad de puntos
                
            \pre <em>cierto</em>
            \post Se devuelve la cantidad de posiciones puntuables (niveles) del parámetro implícito
        */
        int cantidad_puntos() const;

        /** @brief Comprovación de existencia

            \pre <em>cierto<em>
            \post Se devuelve true si la categoría de identificador id existe en el circuito, o
            false en caso contrario
        */
        bool existe(int id) const;
        
        /** @brief Consultora de cantidad de categorías
                
            \pre <em>cierto</em>
            \post Se devuelve la cantidad de categorías que existen en el circuito
        */
        int numero_ctg() const;

        // Destructoras
        
        ~mCategorias();
};

#endif
