#include "torneo.hh"
#include <cmath>

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

bool procesar_partido(int &wsa, int &wsb, int &wga, int &wgb) {
    wsa = wsb = 0;
    wga = wgb = 0;
    string datos;
    cin >> datos;
    if (datos != "0") {
        int i = 0;
        while (i < datos.size()) {
            wsa += (int)datos[i];
            wsb += (int)datos[i+2];
            if ((int)datos[i] > (int)datos[i+2]) wga++;
            else if ((int)datos[i] < (int)datos[i+2]) wgb++;
            i += 3;
        }
        return true;
    }
    return false;
}

void procesar_puntos(const BinTree<int> &resultados, const vector<map<string,Jugador>::iterator> &participantes, const mCategorias &lista_ctg, const int categoria, int i, const int tam) {
    if (not resultados.empty() or i < tam) {
        int puntos = lista_ctg.consultar_ctg(categoria)->second[i];
        participantes[resultados.value()-1]->second.add_stat("puntos", puntos);
        procesar_puntos(resultados.left(), participantes, lista_ctg, categoria, i+1, tam);
        procesar_puntos(resultados.right(), participantes, lista_ctg, categoria, i+1, tam);
    }
    return;
}

BinTree<int> procesar_torneo(const BinTree<int> &cuadro, const vector<map<string,Jugador>::iterator> &participantes) {
    int wsa, wsb, wga, wgb;
    if (not procesar_partido(wsa, wsb, wga, wgb)) return BinTree<int> ();

    BinTree<int> left = procesar_torneo(cuadro.left(), participantes);
    BinTree<int> right = procesar_torneo(cuadro.right(), participantes);

    int winner;
    if (wga > wgb) winner = left.value();
    else winner = right.value();

    participantes[left.value()-1]->second.add_stat("wg", wga);
    participantes[left.value()-1]->second.add_stat("lg", wgb);
    participantes[right.value()-1]->second.add_stat("wg", wgb);
    participantes[right.value()-1]->second.add_stat("lg", wga);

    if (wsa != 0 and wsb != 0) {
        participantes[right.value()-1]->second.add_stat("ws", wsb);
        participantes[right.value()-1]->second.add_stat("ls", wsa);
        participantes[left.value()-1]->second.add_stat("ws", wsa);
        participantes[left.value()-1]->second.add_stat("ls", wsb);
    }

    return BinTree<int> (winner, left, right);
}

void escribir_resultados (/*const BinTree<int> &resultados*/) {
    cout << "hasta aqui funciona!!" << endl;
}

void Torneo::finalizar(const mCategorias &lista_ctg, mJugadores &lista_jug) {
    BinTree<int> resultados = procesar_torneo(cuadro, participantes);
    int tam = lista_ctg.consultar_ctg(categoria)->second.size();
    procesar_puntos(resultados, participantes, lista_ctg, categoria, 0, tam);
    lista_jug.reordenar_rnk();
    escribir_resultados(/*resultados*/);
}

int Torneo::consultar_ctg() const {
    return categoria;
}

Torneo::~Torneo() {}
