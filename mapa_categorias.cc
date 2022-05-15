#include "mapa_categorias.hh"

mCategorias::mCategorias(int c, int k) {
    size = c;
    maxpuntos = k;
    nombres = vector<string> (size);
}

void mCategorias::leer() {
    for (int i = 0; i < size; i++) cin >> nombres[i];
    for (int i = 0; i < size; i++) {
        vector<int> pts(maxpuntos);
        for (int j = 0; j < maxpuntos; j++) cin >> pts[j];
        categorias[nombres[i]] = pts;
    }
}

void mCategorias::escribir() const {
    cout << size << ' ' << maxpuntos << endl;
    for (int i = 0; i < size; i++) {
        cout << nombres[i];
        vector<int> pts = categorias.find(nombres[i])->second;
        for (int j = 0; j < maxpuntos; j++) cout << ' ' << pts[j];
        cout << endl;
    }
}

string mCategorias::consultar_nombre(int id) const {
    return nombres[id-1];
}

int mCategorias::consultar_puntos(int id, int n) const {
    return categorias.find(nombres[id-1])->second[n];
}

int mCategorias::cantidad_puntos() const {
    return categorias.begin()->second.size();
}

int mCategorias::numero_ctg() const {
    return size;
}

bool mCategorias::existe(int n) const {
    return (n <= size and n > 0);
}

mCategorias::~mCategorias() {}
