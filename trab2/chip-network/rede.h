#ifndef REDE_H
#define REDE_H

#include <vector>
#include "roteador.h"
#include "coord.h"

class roteador;

using namespace std;

class rede {
public:
    vector<vector<roteador>> r;

    rede() {
        r = vector<vector<roteador>>(8, vector<roteador>(8));
    }

    bool pode_ir(coord, coord);
    void atualiza(int id_pacote, coord atual, coord proxima);
};

#endif 