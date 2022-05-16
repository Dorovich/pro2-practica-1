/** @file torneo.hh
    @brief Especificación de la clase Torneo
*/

#ifndef TORNEO_HH
#define TORNEO_HH

#include "mapa_categorias.hh"
#include "mapa_jugadores.hh"
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
        BinTree<int> cuadro;
        vector<pair<string,int>> participantes;
        vector<pair<string,int>> exparticipantes;

        /** @brief Crear cuadro de emparejamientos
                
            \pre part es el número de participantes del torneo. altura = 1+ceil(log2(part))
            conflicto es false si no faltan participantes para que el árbol final estuviese
            completo y true en caso contrario. pos es la posición de ranking del nodo actual.
            nivel es el la altura a la que se encuentra el nodo actual.
            \post Se ha devuelto un árbol cuya raíz tiene por valor la posición de ranking del
            hijo izquierdo, a no ser que nivel excediera altura+1 (nodo vacío) o el nivel
            siguiente no estuviese completo (se asigna un jugador directamente)
        */
        BinTree<int> crear_cuadro (const int &altura, const int &part, const bool conflicto, int pos, int nivel);

        /** @brief Escribir cuadro de emparejamientos
            
            \pre <em>cierto</em>
            \post Se ha escrito por el canal estándar de entrada el árbol de emparejamientos
            del torneo
        */
        void escribir_cuadro (const BinTree<int> &c);

        /** @brief Procesar datos del partido
            
            \pre En el canal estándar de entrada estan los resultados de un partido del torneo
            \post Se han añadido a dt los resultados. wsa y wsb son ahora los sets que han ganado
            los participantes de la izquierda y la derecha, respectivamente. wga y wgb son ahora
            los juegos que han ganado dichos participantes. Se devuelve true si se ha disputado
            un partido en este nodo, o false en caso contrario
        */
        bool procesar_partido (list<string> &dt, int &wsa, int &wsb, int &wga, int &wgb);

        /** @brief Crear cuadro de resultados
            
            \pre i es la altura del nodo actual, además de la posición puntuable i de la categoría
            de conj_ctg a la que pertenece el torneo. c es un nodo de altura i del cuadro de
            emparejamientos del torneo
            \post Se ha devuelto un árbol con el valor de c (una posición de ranking de conj_jug) 
            si no se ha disputado un torneo en este nodo, o un árbol cuyo valor es la posición de 
            ranking del ganador entre sus dos hijos. Se han sumados los puntos correspondientes a
            cada perdedor y ganador de cada partido disputado y actualizado sus estadísticas
        */
        BinTree<int> procesar_torneo (const BinTree<int> &c, mJugadores &conj_jug, const mCategorias &conj_ctg, list<string> &dt, int i);

        /** @brief Escribir cuadro de resultados
            
            \pre it apunta al inicio de la lista de resultados de los partidos
            \post Se ha escrito por el canal estándar de entrada el árbol de resultados
            del torneo en preorden (los partidos disputados y sus resultados apuntados
            en preorden por it)
        */
        void escribir_resultados (const BinTree<int> &r, list<string>::iterator &it);

    public:

        // Creadoras
        
        /** @brief Creadora indefinida
                
            \pre <em>cierto</em>
            \post Se ha creado un nuevo torneo sin categoría ni participantes
        */
        Torneo();

        /** @brief Creadora definida
                
            \pre <em>cierto</em>
            \post Se ha creado un nuevo torneo de categoría c y sin participantes
        */
        Torneo(int c);

        // Modificadoras
        
        /** @brief Eliminar ultimas puntuaciones
                
            \pre <em>cierto</em>
            \post Se han eliminado los últimos puntos que ganaron los jugadores de conj_jug
            que participaron en la última edición del torneo
        */
        void purgar_puntos(mJugadores &conj_jug);

        /** @brief Eliminar datos de un jugador

            \pre <em>cierto</em>
            \post Se han eliminado del registro de jugadores de la edición anterior
            al jugador de nombre n
        */
        void purgar_jugador(const string &n);

        /** @brief Iniciar el torneo
                
            \pre El parámetro implícito no se ha iniciado previamente. En el canal estándar
            de entrada hay un entero x, seguido de x posiciones válidas de ranking (existe
            un jugador de conj_jug para cada una).
            \post Se ha confeccionado el cuadro de emparejamientos del torneo y se ha escrito
            por el canal estándar de salida
        */
        void iniciar(mJugadores &lista_jug);

        /** @brief Finalizar el torneo

            \pre El parámetro implícito se ha iniciado previamente. En el canal estándar de
            entrada estan los resultados de los partidos del cuadro de emparejamientos
            \post Se ha confeccionado y escrito por el canal estándar de salida el cuadro de
            resultados del torneo, seguido de los jugadores de conj_jug que han participado y los
            puntos que han obtenido (respecto a la categoría de conj_ctg a la que pertenece el 
            torneo)
        */
        void finalizar(const mCategorias &lista_ctg, mJugadores &lista_jug);

        // Consultoras
        
        /** @brief Consultar categoría
                
            \pre <em>cierto</em>
            \post Se devuelve el valor de la categoría a la que pertenece el parámetro implícito
        */
        int consultar_ctg() const;

        /** @brief Consultar inicio
                
            \pre <em>cierto</em>
            \post Se devuelve true si el torneo ha sido iniciado con anterioridad, y
            false en caso contrario
        */
        bool iniciado() const;

        // Destructora
        
        ~Torneo();

};

#endif
