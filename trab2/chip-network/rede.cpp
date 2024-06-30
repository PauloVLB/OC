#include "rede.h"

bool rede::pode_ir(coord c) const {
    return c.x >= 0 && c.x < 8 && c.y >= 0 && c.y < 8 && !r[c.x][c.y].bloqueado;
}

void rede::atualiza(int id_pacote, coord atual, coord proxima) {}