#include "mapa_torneos.hh"
#include <vector>

mTorneos::mTorneos(int t) {
    size = t;
}

void mTorneos::leer() {
    for (int i = 0; i < size; i++) {
        string id;
        int ctg;
        cin >> id >> ctg;
        torneos[id] = Torneo(ctg);
    }
}

void mTorneos::anadir(string id, int ctg) {
    torneos[id] = Torneo(ctg);
    size++;
    cout << size << endl;
}

void mTorneos::baja(string id, mJugadores &lista_jug) {
    map<string,Torneo>::iterator it = torneos.find(id);
    if (it->second.iniciado()) it->second.purgar_puntos(lista_jug);
    torneos.erase(it);
    size--;
    cout << size << endl;
    lista_jug.reordenar_rnk();
}

void mTorneos::purgar_jugador(string nombre) {
    map<string,Torneo>::iterator it;
    for (it = torneos.begin(); it != torneos.end(); it++) it->second.purgar_jugador(nombre);
}

void mTorneos::iniciar(string id, const mJugadores &lista_jug) {
    torneos[id].iniciar(lista_jug);
}

void mTorneos::finalizar(string id, const mCategorias &lista_ctg, mJugadores &lista_jug) {
    torneos[id].finalizar(lista_ctg, lista_jug);
}

void mTorneos::escribir(const mCategorias &lista_ctg) const {
    cout << size << endl;
    for (map<string,Torneo>::const_iterator it = torneos.begin(); it != torneos.end(); it++) {
        cout << it->first << ' ';
        int index = it->second.consultar_ctg();
        cout << lista_ctg.consultar_nombre(index) << endl;
    }
}

bool mTorneos::existe(string s) const {
    return torneos.end() != torneos.find(s);
}

mTorneos::~mTorneos() {}
