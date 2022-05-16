/** @file mapa_torneos.hh
    @brief Especificación de la clase mTorneos
*/

#ifndef MAPA_TORNEOS_HH
#define MAPA_TORNEOS_HH

#include "torneo.hh"
#include "mapa_jugadores.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <iostream>
using namespace std;
#endif

/** @class mTorneos
    @brief Representa un conjunto de todos los torneos del circuito
*/
class mTorneos {
    private:
        
        map<string,Torneo> torneos;
        int size;
        
    public:
        
        // Creadoras
        
        /** @brief Creadoras indefinida
                
            \pre <em>cierto</em>
            \post Se ha creado una lista vacía de t torneos
        */
        mTorneos(int t);
        
        // Modificadoras
        
        /** @brief Operación de lectura
                
            \pre En el canal estándar de entrada hay tantos nombres seguidos de un identificador de
            categoría válido como declarados al inicio
            \post Se han leído todas los torneos que cabían en la lista inicial
        */
        void leer();
        
        /** @brief Añadir un torneo
                
            \pre ctg es una identificador válido de categoría
            \post Se ha añadido un nuevo torneo con identificador de la categoría ctg a
            la lista
        */
        void anadir(const string &id, int ctg);
        
        /** @brief Dar de baja un torneo
                
            \pre Existe un torneo de nombre id en la lista
            \post Se ha dado de baja el torneo con identificador id, y se han retirado los puntos de
            los jugadores de conj_jug que participaron en su anterior edición, si la hubiera

        */
        void baja(const string &id, mJugadores &conj_jug);

        /** @brief Eliminar datos de un jugador

            \pre <em>cierto</em>
            \post Se han eliminado los datos del jugador de nombre n de los
            registros de todos los torneos
        */
        void purgar_jugador(const string &n);

        /** @brief Iniciar un torneo
                
            \pre El torneo de nombre id existe en el circuito y no se ha iniciado previamente. En el 
            canal estándar de entrada hay un entero x, seguido de x posiciones válidas de ranking 
            (existe un jugador de conj_jug para cada una).
            \post Se ha confeccionado el cuadro de emparejamientos del torneo y se ha escrito por el
            canal estándar de salida
        */
        void iniciar(const string &id, mJugadores &conj_jug);
        
        /** @brief Finalizar un torneo
                
            \pre El torneo de nombre id existe en el circuito y se ha iniciado previamente. En el
            canal estándar de entrada estan los resultados de los partidos del cuadro de emparejamientos
            \post Se ha confeccionado y escrito por el canal estándar de salida el cuadro de
            resultados del torneo, seguido de los jugadores de conj_jug que han participado y los
            puntos que han obtenido (respecto a la categoría de conj_ctg a la que pertenece el torneo)
        */
        void finalizar(const string &id, const mCategorias &conj_ctg, mJugadores &conj_jug);
        
        // Consultoras
        
        /** @brief Operación de escritura
                
            \pre <em>cierto</em>
            \post Se han escrito por el canal estándar de salida, por orden creciente de
            identificador, todos los torneos del circuito y sus puntos con respecto a la categoría de
            conj_ctg que pertenecen
        */
        void escribir(const mCategorias &conj_ctg) const;

        /** @brief Comprovación de existencia

            \pre <em>cierto<em>
            \post Se devuelve true si el torneo de nombre id existe en el circuito, o
            false en caso contrario
        */
        bool existe(const string &id) const;
        
        // Destructora
        
        ~mTorneos();
};

#endif
