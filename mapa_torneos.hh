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
                
            \pre <em>cierto</em>
            \post Se han leído todas los torneos que cabían en la lista
        */
        void leer();
        
        /** @brief Añadir un torneo
                
            \pre <em>cierto</em>
            \post Se ha añadido un nuevo torneo con identificador de la categoría ctg a
            la lista
        */
        void anadir(string id, int ctg);
        
        /** @brief Dar de baja un torneo
                
            \pre Existe un torneo con identificador id en la lista
            \post Se ha dado de baja el torneo con identificador id
        */
        void baja(string id, mJugadores &lista_jug);

        /** @brief Eliminar datos de un jugador

            \pre <em>cierto</em>
            \post Se han eliminado los datos del jugador de nombre "nombre" de los
            registros de todos los torneos
        */
        void purgar_jugador(string nombre);

        /** @brief Iniciar un torneo
                
            \pre <em>cierto</em>
            \post Se ha iniciado el torneo con identificador id
        */
        void iniciar(string id, const mJugadores &lista_jug);
        
        /** @brief Finalizar un torneo
                
            \pre <em>cierto</em>
            \post Se ha finalizado el torneo con identificador id
        */
        void finalizar(string id, const mCategorias &lista_ctg, mJugadores &lista_jug);
        
        // Consultoras
        
        /** @brief Operación de escritura
                
            \pre <em>cierto</em>
            \post Se han escrito por el canal estándar de salida, por orden creciente de
            identificador, todos los torneos del circuito
        */
        void escribir(const mCategorias &lista_ctg) const;

        /** @brief Comprovación de existencia

            \pre <em>cierto<em>
            \post Se devuelve true si el torneo de nombre s existe en el circuito, o
            false en caso contrario
        */
        bool existe(string s) const;
        
        // Destructora
        
        ~mTorneos();
};

#endif
