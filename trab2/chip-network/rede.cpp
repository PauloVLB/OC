#include "rede.h"

bool rede::pode_ir(coord atual, coord quero_ir) {
    if(quero_ir.x < 0 || quero_ir.x >= 8 || quero_ir.y < 0 || quero_ir.y >= 8) return false;
    
    int direcao = r[atual.x][atual.y].direcao(atual, quero_ir);
    if(r[atual.x][atual.y].saida[direcao]) return false;

    int direcao_inv = (direcao + 2) % 4;
    if(r[quero_ir.x][quero_ir.y].entrada[direcao_inv].size() == 4) return false;

    if(r[quero_ir.x][quero_ir.y].bloqueado) return false;

    
    return true;
}

void rede::atualiza(int id_pacote, coord atual, coord proxima) {}