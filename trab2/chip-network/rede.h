#ifndef REDE_H
#define REDE_H

#include <vector>
#include "roteador.h"
#include "coord.h"
#include "pacote.h"

class roteador;
class pacote;

using namespace std;

class rede {
public:
    vector<vector<roteador>> r;

    rede() {
        r = vector<vector<roteador>>(8, vector<roteador>(8));
    }

    bool pode_ir(coord, coord);
    void atualiza(pacote &pck, coord atual, coord proxima);
    void desbloquear_saidas_rede();
    void exclui_pacote(coord atual, int id);
};

#endif 