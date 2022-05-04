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

void Torneo::iniciar(const vector<map<string,Jugador>::iterator> &participantes) {
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
    else return false;
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

void escribir_resultados (const BinTree<int> &resultados) {}

void Torneo::finalizar(const vector<map<string,Jugador>::iterator> &participantes) {
    BinTree<int> resultados = procesar_torneo(cuadro, participantes);
    escribir_resultados(resultados);
    //falta sumar los puntos a cada jugador
    //la clase mJugadores tiene una nueva operacion (reordenar_rnk) que actualiza el ranking segun los puntos
    //luego falta escribirlos y tal
}

int Torneo::consultar_ctg() const {
    return categoria;
}

Torneo::~Torneo() {}
