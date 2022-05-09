#include "torneo.hh"
#include <cmath>
#include <list>
#include <string>

Torneo::Torneo() {
    categoria = 0;
}

Torneo::Torneo(int c) {
    categoria = c;
}

// Operaciones de inicio del torneo

BinTree<int> crear_cuadro (const int &altura, const int &part, const bool conflicto, int pos, int nivel) {
    if (nivel > altura+1) return BinTree<int>();
    else if (conflicto and nivel == altura and pos <= pow(2, altura-1) - part) return BinTree<int>(pos);
    else {
        int maxnodos = pow(2, nivel-1);
        return BinTree<int>(pos, crear_cuadro(altura, part, conflicto, pos, nivel+1), crear_cuadro(altura, part, conflicto, maxnodos+1-pos, nivel+1));
    }
}

void escribir_cuadro (const BinTree<int> &cuadro, const vector<map<string,Jugador>::iterator> &participantes) {
    if (not cuadro.right().empty()) {
        cout << '(';
        escribir_cuadro(cuadro.left(), participantes);
        cout << ' ';
        escribir_cuadro(cuadro.right(), participantes);
        cout << ')';
    }
    else cout << cuadro.value() << '.' << participantes[cuadro.value()-1]->first;
}

void Torneo::iniciar(const vector<map<string,Jugador>::iterator> &p) {
    participantes = p;
    int part = participantes.size();
    int altura = 1+ceil(log2(part));
    int max = pow(2, altura-1);
    bool conflicto = (max != part);

    cuadro = BinTree<int> (1, crear_cuadro(altura, part, conflicto, 1, 3), crear_cuadro(altura, part, conflicto, 2, 3));
    escribir_cuadro(cuadro, participantes);
    cout << endl;
}

// Operaciones de finalización del torneo

void procesar_puntos (const BinTree<pair<int,int>> &resultados, vector<map<string,Jugador>::iterator> &participantes, const vector<int> &puntos, int i) {
    if (resultados.value().second == -1) return;
    map<string,Jugador>::iterator winner = participantes[resultados.value().first-1];
    map<string,Jugador>::iterator loser = participantes[resultados.value().second-1];

    if (i == 0) winner->second.add_stat("puntos", puntos[i]);
    loser->second.add_stat("puntos", puntos[i+1]);

    cout << "(";
    procesar_puntos(resultados.left(), participantes, puntos, i+1);
    cout << winner->first << " vs " << loser->first;
    procesar_puntos(resultados.right(), participantes, puntos, i+1);
    cout << ")";
}

bool procesar_partido(list<string> &dt, int &wsa, int &wsb, int &wga, int &wgb) {
    string datos;
    cin >> datos;
    dt.insert(dt.begin(), datos);
    if (datos == "0") return false;

    wsa = wsb = 0;
    wga = wgb = 0;
    int i = 0;
    while (i < datos.size()) {
        wga += (int)datos[i]-48;
        wgb += (int)datos[i+2]-48;
        if ((int)datos[i] > (int)datos[i+2]) wsa++;
        else wsb++;
        i += 4;
    }
    return true;
}

BinTree<pair<int,int>> procesar_torneo(const BinTree<int> &cuadro, vector<map<string,Jugador>::iterator> &participantes, list<string> &dt) {
    int wsa, wsb, wga, wgb;
    if (not procesar_partido(dt, wsa, wsb, wga, wgb)) {
        pair<int,int> p;
        p.first = cuadro.value();
        p.second = -1;
        return BinTree<pair<int,int>> (p);
    }

    BinTree<int> cleft = cuadro.left();
    BinTree<int> cright = cuadro.right();

    BinTree<pair<int,int>> left = procesar_torneo(cleft, participantes, dt);
    BinTree<pair<int,int>> right = procesar_torneo(cright, participantes, dt);
    map<string,Jugador>::iterator a = participantes[left.value().first-1];
    map<string,Jugador>::iterator b = participantes[right.value().first-1];

    a->second.add_stat("wg", wga);
    a->second.add_stat("lg", wgb);
    b->second.add_stat("wg", wgb);
    b->second.add_stat("lg", wga);
    if ((wsa != 0 and wsb != 1) and (wsa != 1 and wsb != 0)) {
        a->second.add_stat("ws", wsa);
        a->second.add_stat("ls", wsb);
        b->second.add_stat("ws", wsb);
        b->second.add_stat("ls", wsa);
    }

    pair<int,int> winner_loser;
    if (wsa > wsb) {
        winner_loser.first = cleft.value();
        winner_loser.second = cright.value();
        a->second.add_stat("wm", 1);
        b->second.add_stat("lm", 1);
    }
    else {
        winner_loser.first = cright.value();
        winner_loser.second = cleft.value();
        a->second.add_stat("lm", 1);
        b->second.add_stat("wm", 1);
    }

    return BinTree<pair<int,int>> (winner_loser, left, right);
}

//  void escribir_resultados (const BinTree<pair<int,int>> &resultados, vector<map<string,Jugador>::iterator> &participantes, list<string> &datos, list<string>::const_iterator it) {
//      cout << "W.I.P." << endl;
//  }

void Torneo::finalizar(const mCategorias &lista_ctg, mJugadores &lista_jug) {
    vector<int> puntos = lista_ctg.consultar_ctg(categoria-1)->second;
    list<string> datos;
    BinTree<pair<int,int>> resultados = procesar_torneo(cuadro, participantes, datos);

    procesar_puntos(resultados, participantes, puntos, 0);
    cout << endl;

    lista_jug.reordenar_rnk();
    for (int i = 0; i < participantes.size(); i++) participantes[i]->second.add_stat("ts", 1);

//  escribir_resultados(resultados, participantes, datos, datos.begin());
    for (int i = 0; i < participantes.size(); i++)
        cout << i+1 << '.' << participantes[i]->first << ' ' << participantes[i]->second.consultar_stat("puntos") << endl;
}

int Torneo::consultar_ctg() const {
    return categoria;
}

Torneo::~Torneo() {}
