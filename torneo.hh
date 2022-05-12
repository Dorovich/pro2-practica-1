/** @file torneo.hh
    @brief Especificación de la clase Torneo
*/

#ifndef TORNEO_HH
#define TORNEO_HH

#include "mapa_jugadores.hh"
#include "mapa_categorias.hh"
#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <map>
#include <vector>
#include <list>
using namespace std;
#endif

/** @class Torneo
    @brief Representa un torneo en concreto del circuito
*/
class Torneo {
    private:
        
        int categoria;
        bool ini;
        bool debut;
        BinTree<int> cuadro;
        vector<pair<string,int>> participantes;
        vector<pair<string,int>> exparticipantes;

        BinTree<int> crear_cuadro (const int &altura, const int &part, const bool conflicto, int pos, int nivel);
        void escribir_cuadro (const BinTree<int> &c);
        bool procesar_partido (list<string> &dt, int &wsa, int &wsb, int &wga, int &wgb);
        BinTree<int> procesar_torneo (const BinTree<int> &c, mJugadores &lista_jug, const mCategorias &lista_ctg, list<string> &dt, int i);
        void escribir_resultados (const BinTree<int> &r, list<string>::iterator &it);

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
        
        /** @brief Eliminar ultimas puntuaciones
                
            \pre <em>cierto</em>
            \post Se han eliminado los últimos puntos que ganaron los participantes
            de la última edición del torneo
        */
        void purgar_puntos(mJugadores &lista_jug);

        /** @brief Iniciar el torneo
                
            \pre <em>cierto</em>
            \post Se ha creado y escrito el cuadro de emparejamientos del parámetro
            implícito
        */
        void iniciar(const mJugadores &lista_jug);

        /** @brief Finalizar el torneo

            \pre <em>cierto</em>
            \post Se ha configurado y escrito el cuadro de resultados del parámetro
            implícito
        */
        void finalizar(const mCategorias &lista_ctg, mJugadores &lista_jug);

        // Consultoras
        
        /** @brief Consultar categoría
                
            \pre <em>cierto</em>
            \post Se devuelve el valor de la categoría del parámetro implícito
        */
        int consultar_ctg() const;

        /** @brief Consultar si el torneo fue iniciado
                
            \pre <em>cierto</em>
            \post Se devuelve true si el torneo ha sido iniciado con anterioridad, y
            false en caso contrario
        */
        bool iniciado() const;

        // Destructora
        
        ~Torneo();

};

#endif
