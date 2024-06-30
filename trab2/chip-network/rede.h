#ifndef REDE_H
#define REDE_H

#include "roteador.h"
#include "coord.h"

class rede {
public:
    roteador r[8][8];

    bool pode_ir(coord c) const;
    void atualiza(int id_pacote, coord atual, coord proxima);
};

#endif 