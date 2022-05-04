#include "jugador.hh"

Jugador::Jugador() {
    puntos = 0;
    rank = 0;
    ts = wm = lm = ws = ls = wg = lg = 0;
}

Jugador::Jugador(int p) {
    puntos = p;
    rank = 0;
    ts = wm = lm = ws = ls = wg = lg = 0;
}

Jugador::Jugador(int p, int r) {
    puntos = p;
    rank = r;
    ts = wm = lm = ws = ls = wg = lg = 0;
}

int Jugador::consultar_stat(string s) const {
    if (s == "puntos") return puntos;
    if (s == "rank") return rank;
    if (s == "ts") return ts;
    if (s == "wm") return wm;
    if (s == "lm") return lm;
    if (s == "ws") return ws;
    if (s == "ls") return ls;
    if (s == "wg") return wg;
    if (s == "lg") return lg;
    return 0;
}

void Jugador::modificar_stat(string s, int p) {
    if (s == "puntos") puntos = p;
    else if (s == "rank") rank = p;
    else if (s == "ts") ts = p;
    else if (s == "wm") wm = p;
    else if (s == "lm") lm = p;
    else if (s == "ws") ws = p;
    else if (s == "ls") ls = p;
    else if (s == "wg") wg = p;
    else if (s == "lg") lg = p;
    return;
}

void Jugador::add_stat(string s, int p) {
    if (s == "puntos") puntos += p;
    else if (s == "rank") rank += p;
    else if (s == "ts") ts += p;
    else if (s == "wm") wm += p;
    else if (s == "lm") lm += p;
    else if (s == "ws") ws += p;
    else if (s == "ls") ls += p;
    else if (s == "wg") wg += p;
    else if (s == "lg") lg += p;
    return;
}

Jugador::~Jugador() {}
