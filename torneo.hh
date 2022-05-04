/** @file torneo.hh
    @brief Especificación de la clase Torneo
*/

#ifndef TORNEO_HH
#define TORNEO_HH

#include "mapa_jugadores.hh"
#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#endif

/** @class Torneo
    @brief Representa un torneo en concreto del circuito
*/
class Torneo {
    private:
        
        int categoria;
        BinTree<int> cuadro;

    public:

        // Creadoras
        
        /** @brief Creadora indefinida
                
            \pre <em>cierto</em>
            \post Se ha creado un nuevo torneo sin categoría ni emparejamientos
        */
        Torneo();

        /** @brief Creadora definida
                
            \pre <em>cierto</em>
            \post Se ha creado un nuevo torneo de categoría c y sin emparejamientos
        */
        Torneo(int c);

        // Modificadoras
        
        /** @brief Iniciar el torneo
                
            \pre <em>cierto</em>
            \post Se ha creado y escrito el cuadro de emparejamientos del parámetro
            implícito
        */
        void iniciar(const vector<map<string,Jugador>::iterator> &participantes);

        /** @brief Finalizar el torneo

            \pre <em>cierto</em>
            \post Se ha configurado y escrito el cuadro de resultados del parámetro
            implícito
        */
        void finalizar(const vector<map<string,Jugador>::iterator> &participantes) {}

        // Consultoras
        
        /** @brief Consultar categoría
                
            \pre <em>cierto</em>
            \post Se devuelve el valor de la categoría del parámetro implícito
        */
        int consultar_ctg() const;

        // Destructora
        
        ~Torneo();

};

#endif
