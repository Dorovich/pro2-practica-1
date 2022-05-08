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

//  void procesar_puntos(const BinTree<int> &resultados, const vector<map<string,Jugador>::iterator> &participantes, const mCategorias &lista_ctg, const int categoria, int i, const int tam, const string lastwinner) {
//      if (resultados.empty() or i >= tam) return;
//      int puntos = lista_ctg.consultar_ctg(categoria-1)->second[i];
//      string winner = participantes[resultados.value()-1]->first;
//      if (lastwinner != winner) participantes[resultados.value()-1]->second.add_stat("puntos", puntos);

//      cout << "puntos añadidos a " << participantes[resultados.value()-1]->first << ": " << puntos << endl;
//      procesar_puntos(resultados.left(), participantes, lista_ctg, categoria, i+1, tam, winner);
//      procesar_puntos(resultados.right(), participantes, lista_ctg, categoria, i+1, tam, winner);
//  }

bool procesar_partido(int &wsa, int &wsb, int &wga, int &wgb) {
    string datos;
    cin >> datos;
    if (datos == "0") return false;

    wsa = wsb = 0;
    wga = wgb = 0;
    int i = 0;
    while (i < datos.size()) {
        wsa += (int)datos[i]-48;
        wsb += (int)datos[i+2]-48;
        if ((int)datos[i] > (int)datos[i+2]) wga++;
        else wgb++;
        i += 4;
    }
    return true;
}

BinTree<int> procesar_torneo(const BinTree<int> &cuadro, vector<map<string,Jugador>::iterator> &participantes, const vector<int> &puntos, int i) {
    int wsa, wsb, wga, wgb;
    if (not procesar_partido(wsa, wsb, wga, wgb)) return BinTree<int> ();

    BinTree<int> cleft = cuadro.left();
    BinTree<int> cright = cuadro.right();

    BinTree<int> left = procesar_torneo(cleft, participantes, puntos, i+1);
    BinTree<int> right = procesar_torneo(cright, participantes, puntos, i+1);
    map<string,Jugador>::iterator a = participantes[left.value()-1];
    map<string,Jugador>::iterator b = participantes[right.value()-1];

    a->second.add_stat("wg", wga);
    a->second.add_stat("lg", wgb);
    b->second.add_stat("wg", wgb);
    b->second.add_stat("lg", wga);
    if (wsa != 0 and wsb != 0) {
        a->second.add_stat("ws", wsa);
        a->second.add_stat("ls", wsb);
        b->second.add_stat("ws", wsb);
        b->second.add_stat("ls", wsa);
    }

    int winner;
    cout << wga << '-' << wgb << endl;
    if (wga > wgb) {
        winner = cleft.value();
        if (i == 0) a->second.add_stat("puntos", puntos[0]);
        b->second.add_stat("puntos", puntos[i+1]);
        cout << "puntos añadidos al perdedor (" << b->first << "): " << puntos[i+1] << endl;
    }
    else {
        winner = cright.value();
        if (i == 0) b->second.add_stat("puntos", puntos[0]);
        a->second.add_stat("puntos", puntos[i+1]);
        cout << "puntos añadidos al perdedor (" << a->first << "): " << puntos[i+1] << endl;
    }
    return BinTree<int> (winner, left, right);
}

void escribir_resultados (const BinTree<int> &resultados, vector<map<string,Jugador>::iterator> &participantes) {
    for (int i = 0; i < participantes.size(); i++)
        cout << i+1 << ' ' << participantes[i]->first << ' ' << participantes[i]->second.consultar_stat("puntos") << endl;
}

void Torneo::finalizar(const mCategorias &lista_ctg, mJugadores &lista_jug) {
    vector<int> puntos = lista_ctg.consultar_ctg(categoria-1)->second;
    BinTree<int> resultados = procesar_torneo(cuadro, participantes, puntos, 0);
    cout << "DEBUG: torneos procesados..." << endl;

//  int tam = lista_ctg.consultar_ctg(categoria)->second.size();
//  procesar_puntos(resultados, participantes, lista_ctg, categoria, 0, tam, "");
//  cout << "DEBUG: puntos procesados..." << endl;

    lista_jug.reordenar_rnk();

    escribir_resultados(resultados, participantes);
}

int Torneo::consultar_ctg() const {
    return categoria;
}

Torneo::~Torneo() {}
