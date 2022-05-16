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

        /** @brief Operación de comparación
                
            \pre <em>cierto</em>
            \post Se ha devuelto true si los puntos del jugador al que apunta a
            son superiores a los del que apunta b
        */
        bool cmp (map<string,Jugador>::const_iterator a, map<string,Jugador>::const_iterator b);

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
                
            \pre En el canal estándar de entrada hay tantos nombres como jugadores
            fueron declarados inicialmente
            \post Se han leído todos los jugadores que cabían en el conjunto
        */
        void leer ();

        /** @brief Añadir un jugador
                
            \pre No existe un jugador con identificador n en el circuito
            \post Se ha añadido un jugador con identificador n y 0 puntos al mapa
        */
        void anadir (const string &n);

        /** @brief Dar de baja a un jugador
                
            \pre Existe un jugador con identificador n en el circuito
            \post Se ha dado de baja al jugador con identificador n, y sus sucesores han
            subido un puesto en el ranking
        */
        void baja (const string &n);

        /** @brief Sumar estadística

            \pre <em>cierto</em>
            \post La estadística s del jugador de nombre n ha pasado a tener el valor
            que tenía más val
        */
        void add_stat(const string &n, const string &s, int val);

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

        /** @brief Consultar estadística por nombre de jugador

            \pre El jugador de nombre n existe en el circuito, s es una estadística válida
            \post Se ha devuelto el valor de la estadística s del parámetro implícito
        */
        int consultar_stat(const string &n, const string &s) const;

        /** @brief Consultar estadística por posición de ranking

            \pre Existe un jugador en la posición r del ranking, s es una estadística válida
            \post Se ha devuelto el valor de la estadística s del parámetro implícito
        */
        int consultar_stat(int r, const string &s) const;

        /** @brief Consultar nombre de jugador

            \pre Existe un jugador en la posición r del ranking
            \post Se ha devuelto el nombre del jugador de posición de ranking r
        */
        string consultar_nombre(int r) const;

        /** @brief Operación de escritura indefinida
                
            \pre <em>cierto</em>
            \post Se ha escrito por el canal estándar de salida, en orden creciente
            de identificador, el nombre y todas las estadísticas de cada jugador del
            circuito
        */
        void escribir () const;

        /** @brief Operación de escritura definida
                
            \pre Existe un jugador de nombre n en el circuito
            \post Se ha escrito por el canal estándar de salida el nombre y todas las
            estadísticas del jugador de identificador n del circuito
        */
        void escribir (const string &n) const;

        /** @brief Comprovación de existencia

            \pre <em>cierto<em>
            \post Se devuelve true si el jugador de nombre n existe en el circuito, o
            false en caso contrario
        */
        bool existe(const string &n) const;

        // Destructora
        
        ~mJugadores();
};

#endif
