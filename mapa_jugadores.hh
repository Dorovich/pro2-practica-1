/** @file mapa_jugadores.hh
    @brief Especificación de la clase mJugadores
*/

#ifndef MAPA_JUGADORES_HH
#define MAPA_JUGADORES_HH

#include "jugador.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <vector>
#include <iostream>
using namespace std;
#endif

/** @class mJugadores
    @brief Representa un conjunto de todos los jugadores del circuito
*/
class mJugadores {
    private:
        
        vector<map<string,Jugador>::iterator> rnk;
        map<string,Jugador> jugadores;
        int size;

    public:
        
        // Creadoras
        
        /** @brief Creadora indefinida
                
            \pre <em>cierto</em>
            \post Se ha creado un mapa vacío de tamaño 0
        */
        mJugadores();

        /** @brief Creadora definida
                
            \pre <em>cierto</em>
            \post Se ha creado un mapa vacío de tamaño p
        */
        mJugadores (int p);
        
        // Modificadoras
        
        /** @brief Operación de lectura
                
            \pre <em>cierto</em>
            \post Se han leído tantos jugadores como tamaño tiene el mapa
        */
        void leer ();

        /** @brief Añadir un jugador
                
            \pre No existe un jugador con identificador n en el mapa
            \post Se ha añadido un jugador con identificador n y 0 puntos al mapa
        */
        void anadir (string n);

        /** @brief Dar de baja a un jugador
                
            \pre Existe un jugador con identificador n en el mapa
            \post Se ha dado de baja al jugador con identificador n, y sus sucesores han
            subido un puesto en el ranking
        */
        void baja (string n);

        /** @brief Añadir a atributo

            \pre <em>cierto</em>
            \post El atributo stat del jugador de posición de ranking rank ha pasado a tener
            el valor que tenía más val
        */
        //void add_stat(int rank, string stat, int val);

        /** @brief Añadir a atributo

            \pre <em>cierto</em>
            \post El atributo stat del jugador de nombre "nombre" ha pasado a tener
            el valor que tenía más val
        */
        void add_stat(string nombre, string stat, int val);

        /** @brief Reordenar ranking

            \pre <em>cierto</em>
            \post Se ha actualizado el ranking según los puntos de los jugadores
        */
        void reordenar_rnk ();
        
        // Consultoras
        
        /** @brief Operación de escritura del ranking
                
            \pre <em>cierto</em>
            \post Se ha escrito por el canal estándar de salida, en orden creciente de 
            identificador, la posición, el nombre y las estadísticas de cada jugador 
            del circuito
        */
        void ranking ();

        /** @brief Consultar atributo de jugador

            \pre <em>cierto</em>
            \post Se ha devuelto el valor del atributo stat del jugador de nombre "nombre"
        */
        int consultar_stat(string nombre, string stat) const;

        /** @brief Consultar atributo de jugador

            \pre <em>cierto</em>
            \post Se ha devuelto el valor del atributo stat del jugador de posición de
            ranking rank
        */
        int consultar_stat(int rank, string stat) const;

        /** @brief Consultar nombre de jugador

            \pre <em>cierto</em>
            \post Se ha devuelto el nombre del jugador de posición de ranking rank
        */
        string consultar_nombre(int rank) const;

        /** @brief Operación de escritura indefinida
                
            \pre <em>cierto</em>
            \post Se ha escrito por el canal estándar de salida, en orden creciente
            de identificador, el nombre y todas las estadísticas de cada jugador del
            circuito
        */
        void escribir () const;

        /** @brief Operación de escritura definida
                
            \pre Existe un jugador con identificador n en el mapa
            \post Se ha escrito por el canal estándar de salida el nombre y todas las
            estadísticas del jugador de identificador n del circuito
        */
        void escribir (string n) const;

        /** @brief Comprovación de existencia

            \pre <em>cierto<em>
            \post Se devuelve true si el jugador de nombre n existe en el circuito, o
            false en caso contrario
        */
        bool existe(string n) const;

        // Destructora
        
        ~mJugadores();
};

#endif
