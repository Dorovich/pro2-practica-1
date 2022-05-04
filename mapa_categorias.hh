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
        vector<map<string,vector<int>>::iterator> ids;
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
                
            \pre <em>cierto</em>
            \post Se han leido todas las categorías que cabían en la lista
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

        /** @brief Consultora por índice
                
            \pre <em>cierto</em>
            \post Se devuelve el nombre de la categoría de índice n del parámetro implícito
        */
        string consultar_ctg(int n) const;

        /** @brief Comprovación de existencia

            \pre <em>cierto<em>
            \post Se devuelve true si la categoría de nombre n existe en el circuito, o
            false en caso contrario
        */
        bool existe(int n) const;
        
        /** @brief Consultora de cantidad de categorías
                
            \pre <em>cierto</em>
            \post Se devuelve la cantidad de categorías que existen
        */
        int numero_ctg() const;

        // Destructoras
        
        ~mCategorias();
};

#endif
