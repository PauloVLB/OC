#ifndef INSTANCIA_H
#define INSTANCIA_H

#include <vector>
#include "coord.h"
#include "pacote.h"

class instancia {
public:
    int tempo;
    coord orig, dest;
    vector<int> pacotes_info;
    instancia(int t, coord o, coord d, const vector<int>& p) : tempo{t}, orig{o}, dest{d}, pacotes_info{p} {}

    pacote criar_pacote(int id, int tempo_saida) {
        pacote novo_pacote = pacote(orig, dest, id, pacotes_info.back(), tempo_saida);
        pacotes_info.pop_back();

        return novo_pacote;
    }

    bool tem_pacote() {
        return !pacotes_info.empty();
    }

    bool operator<(const instancia& o) {
        return tempo < o.tempo;
    }
};

#endif // INSTANCIA_H