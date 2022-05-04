#include "mapa_torneos.hh"
#include "mapa_jugadores.hh"
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

void mTorneos::baja(string id) {
    map<string,Torneo>::const_iterator it = torneos.find(id);
    torneos.erase(it);
    size--;
    cout << size << endl;
}

void mTorneos::iniciar(string id, const mJugadores &lista_jug) {
    int p;
    cin >> p;
    vector<map<string,Jugador>::iterator> participantes(p);
    for (int i = 0; i < p; i++) {
        int pos;
        cin >> pos;
        participantes[i] = lista_jug.consultar_rnk(pos-1);
    }
    torneos[id].iniciar(participantes);
}

void mTorneos::finalizar(string id, const vector<map<string,Jugador>::iterator> &participantes) {
    torneos[id].finalizar(participantes);
}

void mTorneos::escribir(const mCategorias &lista_ctg) const {
    cout << size << endl;
    for (map<string,Torneo>::const_iterator it = torneos.begin(); it != torneos.end(); it++) {
        cout << it->first << ' ';
        int index = it->second.consultar_ctg();
        cout << lista_ctg.consultar_ctg(index-1) << endl;
    }
}

bool mTorneos::existe(string s) const {
    return torneos.end() != torneos.find(s);
}

mTorneos::~mTorneos() {}
