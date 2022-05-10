#include "mapa_jugadores.hh"
#include "jugador.hh"
#include <list>
#include <algorithm>

mJugadores::mJugadores() {
    size = 0;
}

mJugadores::mJugadores(int p) {
    size = p;
    rnk = vector<map<string,Jugador>::iterator> (p);
}

void mJugadores::leer() {
    for (int i = 0; i < size; i++) {
        string s;
        cin >> s;
        jugadores[s] = Jugador(0);
        jugadores[s].modificar_stat("rank", i+1);
        rnk[i] = jugadores.find(s);
    }
}

void mJugadores::anadir(string n) {
    jugadores[n] = Jugador(0, size+1);
    rnk.push_back(jugadores.find(n));
    size++;
    cout << size << endl;
}

void mJugadores::baja(string n) {
    map<string,Jugador>::iterator it = jugadores.find(n);
    int i = 0;
    while (rnk[i] != it) i++;
    while (i < size-1) {
        map<string,Jugador>::iterator aux = rnk[i];
        rnk[i] = rnk[i+1];
        rnk[i+1] = aux;
        rnk[i]->second.modificar_stat("rank", i+1);
        i++;
    }
    rnk.pop_back();
    jugadores.erase(it);
    size--;
    cout << size << endl;
}

bool cmp (map<string,Jugador>::const_iterator a, map<string,Jugador>::const_iterator b) {
    int puntos_a = a->second.consultar_stat("puntos");
    int puntos_b = b->second.consultar_stat("puntos");
    int rank_a = a->second.consultar_stat("rank");
    int rank_b = b->second.consultar_stat("rank");

    if (puntos_a > puntos_b) return true;
    else if (puntos_a == puntos_b and rank_a < rank_b) return true;
    return false;
}

void mJugadores::ranking() {
    sort(rnk.begin(), rnk.end(), cmp);
    for (int i = 0; i < size; i++) rnk[i]->second.modificar_stat("rank", i+1);
    for (int i = 0; i < size; i++) {
        cout << rnk[i]->second.consultar_stat("rank") << ' ' << rnk[i]->first << ' ' << rnk[i]->second.consultar_stat("puntos") << endl;
    }
}

void mJugadores::reordenar_rnk() {
    sort(rnk.begin(), rnk.end(), cmp);
    for (int i = 0; i < size; i++) rnk[i]->second.modificar_stat("rank", i+1);
}

void mJugadores::escribir() const {
    cout << size << endl;
    map<string,Jugador>::const_iterator it = jugadores.begin();
    while (it != jugadores.end()) {
        cout << it->first << ' ';
        cout << "Rk:" << it->second.consultar_stat("rank") << ' ';
        cout << "Ps:" << it->second.consultar_stat("puntos") << ' ';
        cout << "Ts:" << it->second.consultar_stat("ts") << ' ';
        cout << "WM:" << it->second.consultar_stat("wm") << ' ';
        cout << "LM:" << it->second.consultar_stat("lm") << ' ';
        cout << "WS:" << it->second.consultar_stat("ws") << ' ';
        cout << "LS:" << it->second.consultar_stat("ls") << ' ';
        cout << "WG:" << it->second.consultar_stat("wg") << ' ';
        cout << "LG:" << it->second.consultar_stat("lg") << endl;
        it++;
    }
}

void mJugadores::escribir(string s) const {
    map<string,Jugador>::const_iterator it = jugadores.find(s);
    cout << it->first << ' ';
    cout << "Rk:" << it->second.consultar_stat("rank") << ' ';
    cout << "Ps:" << it->second.consultar_stat("puntos") << ' ';
    cout << "Ts:" << it->second.consultar_stat("ts") << ' ';
    cout << "WM:" << it->second.consultar_stat("wm") << ' ';
    cout << "LM:" << it->second.consultar_stat("lm") << ' ';
    cout << "WS:" << it->second.consultar_stat("ws") << ' ';
    cout << "LS:" << it->second.consultar_stat("ls") << ' ';
    cout << "WG:" << it->second.consultar_stat("wg") << ' ';
    cout << "LG:" << it->second.consultar_stat("lg") << endl;
}

map<string,Jugador>::iterator mJugadores::consultar_rnk(int i) const {
    return rnk[i];
}

bool mJugadores::existe(string n) const {
    return jugadores.end() != jugadores.find(n);
}

mJugadores::~mJugadores() {}
