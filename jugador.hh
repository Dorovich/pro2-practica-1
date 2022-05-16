/** @file jugador.hh
    @brief Especificación de la clase Jugador
*/

#ifndef JUGADOR_HH
#define JUGADOR_HH

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Jugador
    @brief Representa un jugador específico del circuito
*/
class Jugador {
    private:
            
        // el objeto jugador no tiene un nombre asociado, lo tiene en el mapa
        int puntos, rank;

        /* INFO STATS RAROS
            ts: torneos en que ha participado (incrementar al acabar)
            wm: won matches
            lm: lost matches
            ws: won sets
            ls: lost sets
            wg: won games
            lg: lost games
        */
        int ts, wm, lm, ws, ls, wg, lg;
            
    public:
        
        // Creadoras
        
        /** @brief Creadora indefinida
                
            \pre <em>cierto</em>
            \post Se ha creado un nuevo jugador sin puntos ni estadísticas
        */
        Jugador();

        /** @brief Creadora definida
                
            \pre <em>cierto</em>
            \post Se ha creado un nuevo jugador con p puntos y sin estadísticas
        */
        Jugador(int p);

        /** @brief Creadora definida con ranking
                
            \pre <em>cierto</em>
            \post Se ha creado un nuevo jugador con p puntos, ranking r y sin estadísticas
        */
        Jugador(int p, int r);
        
        // Modificadoras
        
        /** @brief Modificar estadística
                
            \pre s es una de las estadísticas de los jugadores
            \post La estadística s del parámetro implícito ha pasado a ser p
        */
        void modificar_stat (const string &s, int p);

        /** @brief Suma a estadística

            \pre s es una de las estadísticas de los jugadores
            \post La estadística s del parámetro implícito ha pasado a ser el valor que
            tenía más p
        */
        void add_stat (const string &s, int p);
        
        // Consultoras
        
        /** @brief Consultar estadística
                
            \pre s es una de las estadísticas de los jugadores
            \post Se devuelve el valor de la estadística s del parámetro implícito
        */
        int consultar_stat(const string &s) const;
        
        // Destructoras
        
        ~Jugador();
};

#endif
