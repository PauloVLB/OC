#ifndef ROTEADOR_H
#define ROTEADOR_H

#include <vector>
#include "pacote.h"
#include "coord.h"

using namespace std;

class pacote;

class roteador {
public:
    vector<pacote> entrada[4]; // entrada[i][j] -> pacote na posição j da entrada i
    bool saida[4];
    bool bloqueado = false;

    int direcao(coord atual, coord destino);
};

#endif