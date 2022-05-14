#include <iostream>
#include "mapa_categorias.hh"
#include "mapa_jugadores.hh"
#include "mapa_torneos.hh"
using namespace std;

int main () {

    // leer categorias
    int c, k;
    cin >> c >> k;
    mCategorias C(c, k);
    C.leer();
    
    // leer torneos iniciales
    int t;
    cin >> t;
    mTorneos T(t);
    T.leer();

    // leer jugadores iniciales
    int p;
    cin >> p;
    mJugadores P(p);
    P.leer();
    
    // leer y procesar comandos
    string cmd;
    while (cin >> cmd and cmd != "fin") {
        if (cmd == "nuevo_jugador" or cmd == "nj") {
            string p;
            cin >> p;
            cout << "#" << cmd << " " << p << endl;
            if (P.existe(p)) cout << "error: ya existe un jugador con ese nombre" << endl;
            else P.anadir(p);
        }
        else if (cmd == "nuevo_torneo" or cmd == "nt") {
            string t;
            int c;
            cin >> t >> c;
            cout << "#" << cmd << " " << t << " " << c << endl;
            if (T.existe(t)) cout << "error: ya existe un torneo con ese nombre" << endl;
            else if (not C.existe(c)) cout << "error: la categoria no existe" << endl;
            else T.anadir(t, c);
        }
        else if (cmd == "baja_jugador" or cmd == "bj") {
            string p;
            cin >> p;
            cout << "#" << cmd << " " << p << endl;
            if (not P.existe(p)) cout << "error: el jugador no existe" << endl;
            else {
                T.purgar_jugador(p);
                P.baja(p);
            }
        }
        else if (cmd == "baja_torneo" or cmd == "bt") {
            string t;
            cin >> t;
            cout << "#" << cmd << " " << t << endl;
            if (not T.existe(t)) cout << "error: el torneo no existe" << endl;
            else T.baja(t, P);
        }
        else if (cmd == "iniciar_torneo" or cmd == "it") {
            string t;
            cin >> t;
            cout << "#" << cmd << " " << t << endl;
            T.iniciar(t, P);
        }
        else if (cmd == "finalizar_torneo" or cmd == "ft") {
            string t;
            cin >> t;
            cout << "#" << cmd << " " << t << endl;
            T.finalizar(t, C, P);
        }
        else if (cmd == "consultar_jugador" or cmd == "cj") {
            string n;
            cin >> n;
            cout << "#" << cmd << " " << n << endl;
            if (not P.existe(n)) cout << "error: el jugador no existe" << endl;
            else P.escribir(n);
        }
        else if (cmd == "listar_ranking" or cmd == "lr") {
            cout << "#" << cmd << endl;
            P.ranking();
        }
        else if (cmd == "listar_jugadores" or cmd == "lj") {
            cout << "#" << cmd << endl;
            P.escribir();
        }
        else if (cmd == "listar_torneos" or cmd == "lt") {
            cout << "#" << cmd << endl;
            T.escribir(C);
        }
        else if (cmd == "listar_categorias" or cmd == "lc") { 
            cout << "#" << cmd << endl;
            C.escribir();
        }
    }
}
