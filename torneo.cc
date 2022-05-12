#include "torneo.hh"
#include <cmath>

Torneo::Torneo() {
    categoria = 0;
    ini = false;
    debut = true;
}

Torneo::Torneo(int c) {
    categoria = c;
    ini = false;
    debut = true;
}

void Torneo::purgar_puntos(mJugadores &lista_jug) {
    for (int i = 0; i < exparticipantes.size(); i++) {
        lista_jug.add_stat(exparticipantes[i].first, "puntos", -exparticipantes[i].second);
    }
}

int Torneo::consultar_ctg() const {
    return categoria;
}

bool Torneo::iniciado() const {
    return ini;
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

void Torneo::iniciar(const mJugadores &lista_jug) {
    if (not ini) ini = true;
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
        wga += (int)dts[i]-48;
        wgb += (int)dts[i+2]-48;
        if ((int)dts[i] > (int)dts[i+2]) wsa++;
        else wsb++;
        i += 4;
    }
    return true;
}

BinTree<int> Torneo::procesar_torneo(const BinTree<int> &c, mJugadores &lista_jug, const mCategorias &lista_ctg, list<string> &dt, int i) {
    int wsa, wsb, wga, wgb;
    if (not procesar_partido(dt, wsa, wsb, wga, wgb)) return BinTree<int> (c.value(), BinTree<int> (), BinTree<int> ());

    //BinTree<int> cleft = c.left();
    //BinTree<int> cright = c.right();

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

    int puntos = lista_ctg.consultar_puntos(categoria, i+1);
    if (wsa > wsb) {
        if (i == 0) {
            int puntosmax = lista_ctg.consultar_puntos(categoria, 0);
            participantes[a].second += puntosmax;
            exparticipantes[a].second = puntosmax;
        }
        participantes[b].second += puntos;
        exparticipantes[b].second = puntos;

        lista_jug.add_stat(participantes[a].first, "wm", 1);
        lista_jug.add_stat(participantes[b].first, "lm", 1);

        //gana el jugador izquierdo
        return BinTree<int> (a+1, left, right);
    }
    else {
        if (i == 0) {
            int puntosmax = lista_ctg.consultar_puntos(categoria, 0);
            participantes[b].second += puntosmax;
            exparticipantes[b].second = puntosmax;
        }
        participantes[a].second += puntos;
        exparticipantes[a].second = puntos;

        lista_jug.add_stat(participantes[a].first, "lm", 1);
        lista_jug.add_stat(participantes[b].first, "wm", 1);

        //gana el jugador derecho
        return BinTree<int> (b+1, left, right);
    }
}

void Torneo::escribir_resultados (const BinTree<int> &r, list<string>::iterator &it) {
    if (r.right().empty()) return;
    int a = r.left().value(), b = r.right().value();
    cout << '(';
    cout << a << '.' << participantes[a-1].first;
    cout << " vs ";
    cout << b << '.' << participantes[b-1].first;
    cout << " " << *it;
    ++it;
    escribir_resultados(r.left(), it);
    escribir_resultados(r.right(), it);
    cout << ')';
}

void Torneo::finalizar(const mCategorias &lista_ctg, mJugadores &lista_jug) {
    //si el torneo no debuta, borrar puntos anteriores de los jugadores repetidos
    if (debut) debut = false;
    else purgar_puntos(lista_jug);

    //inicializar vector de puntos, datos y cuadro de resultados
    //y tambien exparticipantes (si los hubiera ya san sido comprovados)
    list<string> datos;
    exparticipantes = vector<pair<string,int>> (participantes.size());
    BinTree<int> resultados = procesar_torneo(cuadro, lista_jug, lista_ctg, datos, 0);

    //escribir arbol de resultados
    list<string>::iterator it = datos.begin();
    escribir_resultados(resultados, it);
    cout << endl;

    //actualizar exparticipantes
    //sumar puntos ganados
    //contar participacion en el torneo
    //escribir los puntos ganados
    for (int i = 0; i < participantes.size(); i++) {
        exparticipantes[i].first = participantes[i].first;
        exparticipantes[i].second = participantes[i].second;
        lista_jug.add_stat(participantes[i].first, "puntos", participantes[i].second);
        lista_jug.add_stat(participantes[i].first, "ts", 1);
        cout << i+1 << '.' << participantes[i].first << ' ' << participantes[i].second << endl;
    }

    //reordenar ranking despues de añadir puntos
    lista_jug.reordenar_rnk();
}
