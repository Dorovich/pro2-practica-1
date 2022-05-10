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

bool procesar_partido(list<string> &dt, int &wsa, int &wsb, int &wga, int &wgb) {
    string datos;
    cin >> datos;
    if (datos == "0") return false;
    else dt.insert(dt.end(), datos);

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

BinTree<int> procesar_torneo(const BinTree<int> &cuadro, vector<map<string,Jugador>::iterator> &participantes, list<string> &dt, const vector<int> &puntos, int i) {
    int wsa, wsb, wga, wgb;
    if (not procesar_partido(dt, wsa, wsb, wga, wgb)) return BinTree<int> (cuadro.value(), BinTree<int> (), BinTree<int> ());

    BinTree<int> cleft = cuadro.left();
    BinTree<int> cright = cuadro.right();

    BinTree<int> left = procesar_torneo(cleft, participantes, dt, puntos, i+1);
    BinTree<int> right = procesar_torneo(cright, participantes, dt, puntos, i+1);
    map<string,Jugador>::iterator a = participantes[left.value()-1];
    map<string,Jugador>::iterator b = participantes[right.value()-1];

    a->second.add_stat("ws", wsa);
    a->second.add_stat("ls", wsb);
    b->second.add_stat("ws", wsb);
    b->second.add_stat("ls", wsa);
    if ((wga != 0 and wgb != 1) and (wga != 0 and wgb != 1)) {
        a->second.add_stat("wg", wga);
        a->second.add_stat("lg", wgb);
        b->second.add_stat("wg", wgb);
        b->second.add_stat("lg", wga);
    }

    int winner;
    if (wsa > wsb) {
        winner = left.value();
        if (i == 0) a->second.add_stat("puntos", puntos[0]);
        b->second.add_stat("puntos", puntos[i+1]);
        a->second.add_stat("wm", 1);
        b->second.add_stat("lm", 1);
    }
    else {
        winner = right.value();
        if (i == 0) b->second.add_stat("puntos", puntos[0]);
        a->second.add_stat("puntos", puntos[i+1]);
        a->second.add_stat("lm", 1);
        b->second.add_stat("wm", 1);
    }

    return BinTree<int> (winner, left, right);
}

void escribir_torneos (const BinTree<int> &resultados, vector<map<string,Jugador>::iterator> &participantes, list<string> &datos, list<string>::const_iterator it) {
    if (resultados.left().empty() or resultados.right().empty()) return;
    int a = resultados.left().value(), b = resultados.right().value();
    cout << a << "." << participantes[a-1]->first << " vs " << b << "." << participantes[b-1]->first;
    cout << " " << *it << "(";
    it++;
    escribir_torneos(resultados.left(), participantes, datos, it);
    it++;
    escribir_torneos(resultados.right(), participantes, datos, it);
    cout << ")";
}

void Torneo::finalizar(const mCategorias &lista_ctg, mJugadores &lista_jug) {
    vector<int> puntos = lista_ctg.consultar_ctg(categoria-1)->second;
    list<string> datos;
    BinTree<int> resultados = procesar_torneo(cuadro, participantes, datos, puntos, 0);

    lista_jug.reordenar_rnk();
    for (int i = 0; i < participantes.size(); i++) participantes[i]->second.add_stat("ts", 1);

    cout << "(";
    escribir_torneos(resultados, participantes, datos, datos.begin());
    cout << ")" << endl;

    for (int i = 0; i < participantes.size(); i++)
        cout << i+1 << '.' << participantes[i]->first << ' ' << participantes[i]->second.consultar_stat("puntos") << endl;
}

int Torneo::consultar_ctg() const {
    return categoria;
}

Torneo::~Torneo() {}
