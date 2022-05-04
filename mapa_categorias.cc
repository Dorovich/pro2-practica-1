#include "mapa_categorias.hh"

mCategorias::mCategorias(int c, int k) {
    size = c;
    maxpuntos = k;
    ids = vector<map<string,vector<int>>::iterator> (size);
}

void mCategorias::leer() {
    vector<string> names(size);
    for (int i = 0; i < size; i++) cin >> names[i];
    for (int i = 0; i < size; i++) {
        vector<int> pts(maxpuntos);
        for (int j = 0; j < maxpuntos; j++) cin >> pts[j];
        categorias[names[i]] = pts;
        ids[i] = categorias.find(names[i]);
    }
}

void mCategorias::escribir() const {
    cout << size << ' ' << maxpuntos << endl;
    for (int i = 0; i < size; i++) {
        cout << ids[i]->first;
        for (int j = 0; j < maxpuntos; j++) cout << ' ' << ids[i]->second[j];
        cout << endl;
    }
}

string mCategorias::consultar_ctg(int n) const {
    return ids[n]->first;
}

int mCategorias::numero_ctg() const {
    return size;
}

bool mCategorias::existe(int n) const {
    return (n <= size and n > 0);
}

mCategorias::~mCategorias() {}
