#include "torneo.hh"
#include <cmath>

Torneo::Torneo() {
    categoria = 0;
    participantes = vector<pair<string,int>> (0);
    exparticipantes = vector<pair<string,int>> (0);
}

Torneo::Torneo(int c) {
    categoria = c;
    participantes = vector<pair<string,int>> (0);
    exparticipantes = vector<pair<string,int>> (0);
}

void Torneo::purgar_puntos(mJugadores &lista_jug) {
    for (int i = 0; i < exparticipantes.size(); i++) {
        if (exparticipantes[i].second != 0) lista_jug.add_stat(exparticipantes[i].first, "puntos", -exparticipantes[i].second);
    }
}

void Torneo::purgar_jugador(const string &nombre) {
    if (participantes.size() == 0) return;

    bool found = false;
    int i = 0;
    while (not found and i < exparticipantes.size()) {
        found = exparticipantes[i].first == nombre;
        i++;
    }
    if (found) {
        exparticipantes[i-1].first = "";
        exparticipantes[i-1].second = 0;
    }
}

int Torneo::consultar_ctg() const {
    return categoria;
}

bool Torneo::iniciado() const {
    return participantes.size() != 0;
}

Torneo::~Torneo() {}

// Operaciones de inicio del torneo

BinTree<int> Torneo::crear_cuadro(const int &altura, const int &part, const bool conflicto, int pos, int nivel) {
    if (nivel > altura+1) return BinTree<int>();
    else if (conflicto and nivel == altura and pos <= pow(2, altura-1) - part) return BinTree<int>(pos);
    else {
        int maxnodos = pow(2, nivel-1);
        return BinTree<int>(pos, crear_cuadro(altura, part, conflicto, pos, nivel+1), crear_cuadro(altura, part, conflicto, maxnodos+1-pos, nivel+1));
    }
}

void Torneo::escribir_cuadro(const BinTree<int> &c) {
    if (not c.right().empty()) {
        cout << '(';
        escribir_cuadro(c.left());
        cout << ' ';
        escribir_cuadro(c.right());
        cout << ')';
    }
    else cout << c.value() << '.' << participantes[c.value()-1].first;
}

void Torneo::iniciar(mJugadores &lista_jug) {
    int size;
    cin >> size;

    participantes = vector<pair<string,int>> (size);
    for (int i = 0; i < size; i++) {
        int pos;
        cin >> pos;
        participantes[i].first = lista_jug.consultar_nombre(pos);
        participantes[i].second = 0;
    }

    int altura = 1+ceil(log2(size));
    int max = pow(2, altura-1);
    bool conflicto = (max != size);

    cuadro = BinTree<int> (1, crear_cuadro(altura, size, conflicto, 1, 3), crear_cuadro(altura, size, conflicto, 2, 3));
    escribir_cuadro(cuadro);
    cout << endl;
}

// Operaciones de finalización del torneo

bool Torneo::procesar_partido(list<string> &dt, int &wsa, int &wsb, int &wga, int &wgb) {
    string dts;
    cin >> dts;
    if (dts == "0") return false;
    else dt.insert(dt.end(), dts);

    wsa = wsb = 0;
    wga = wgb = 0;
    int i = 0;
    while (i < dts.size()) {
        int g_a = (int)dts[i]-48;
        int g_b = (int)dts[i+2]-48;
        wga += g_a;
        wgb += g_b;
        if (g_a > g_b) wsa++;
        else wsb++;
        i += 4;
    }
    return true;
}

BinTree<int> Torneo::procesar_torneo(const BinTree<int> &c, mJugadores &lista_jug, const mCategorias &lista_ctg, list<string> &dt, int i) {
    int wsa, wsb, wga, wgb;
    if (not procesar_partido(dt, wsa, wsb, wga, wgb)) return BinTree<int> (c.value(), BinTree<int> (), BinTree<int> ());

    BinTree<int> left = procesar_torneo(c.left(), lista_jug, lista_ctg, dt, i+1);
    BinTree<int> right = procesar_torneo(c.right(), lista_jug, lista_ctg, dt, i+1);
    int a = left.value()-1;
    int b = right.value()-1;

    if (not (wga == 0 and wgb == 1) and not (wga == 1 and wgb == 0)) {
        lista_jug.add_stat(participantes[a].first, "ws", wsa);
        lista_jug.add_stat(participantes[a].first, "ls", wsb);
        lista_jug.add_stat(participantes[b].first, "ws", wsb);
        lista_jug.add_stat(participantes[b].first, "ls", wsa);
        lista_jug.add_stat(participantes[a].first, "wg", wga);
        lista_jug.add_stat(participantes[a].first, "lg", wgb);
        lista_jug.add_stat(participantes[b].first, "wg", wgb);
        lista_jug.add_stat(participantes[b].first, "lg", wga);
    }
    
    //comprovar si la posicion es puntuable
    if (i <= lista_ctg.cantidad_puntos()) {
        if (wsa > wsb) {
            if (i == 1) participantes[a].second = lista_ctg.consultar_puntos(categoria, 0);
            participantes[b].second = lista_ctg.consultar_puntos(categoria, i);
        }
        else {
            if (i == 1) participantes[b].second = lista_ctg.consultar_puntos(categoria, 0);
            participantes[a].second = lista_ctg.consultar_puntos(categoria, i);
        }
    }

    //decidir ganador
    int winner;
    if (wsa > wsb) {
        winner = a+1;
        lista_jug.add_stat(participantes[a].first, "wm", 1);
        lista_jug.add_stat(participantes[b].first, "lm", 1);
    }
    else {
        winner = b+1;
        lista_jug.add_stat(participantes[a].first, "lm", 1);
        lista_jug.add_stat(participantes[b].first, "wm", 1);
    }
    return BinTree<int> (winner, left, right);
}

void Torneo::escribir_resultados (const BinTree<int> &r, list<string>::iterator &it) {
    if (r.right().empty()) return;
    int a = r.left().value(), b = r.right().value();
    cout << '(';
    cout << a << '.' << participantes[a-1].first;
    cout << " vs ";
    cout << b << '.' << participantes[b-1].first;
    cout << ' ' << *it;
    ++it;
    escribir_resultados(r.left(), it);
    escribir_resultados(r.right(), it);
    cout << ')';
}

void Torneo::finalizar(const mCategorias &lista_ctg, mJugadores &lista_jug) {
    if (exparticipantes.size() != 0) purgar_puntos(lista_jug);

    list<string> datos;
    BinTree<int> resultados = procesar_torneo(cuadro, lista_jug, lista_ctg, datos, 1);
    list<string>::iterator it = datos.begin();
    escribir_resultados(resultados, it);
    cout << endl;

    exparticipantes = vector<pair<string,int>> (participantes.size());
    for (int i = 0; i < participantes.size(); i++) {
        exparticipantes[i].first = participantes[i].first;
        exparticipantes[i].second = participantes[i].second;
        lista_jug.add_stat(participantes[i].first, "ts", 1);
        lista_jug.add_stat(participantes[i].first, "puntos", participantes[i].second);
        if (participantes[i].second != 0) {
            cout << i+1 << '.' << participantes[i].first << ' ' << participantes[i].second << endl;
        }
    }

    lista_jug.reordenar_rnk();
}
