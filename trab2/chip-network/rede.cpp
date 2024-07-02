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

void rede::atualiza(pacote &pck, coord atual, coord proxima) {

    // Achar e remover pacote do roteador atual
    exclui_pacote(atual, pck.id);

    // Adicionar pacote no roteador que ele quer ir
    int direcao = r[atual.x][atual.y].direcao(atual, proxima);
    r[proxima.x][proxima.y].entrada[(direcao + 2) % 4].push_back(pck);

    // Atualizar a posição do pacote
    pck.atual = proxima;
    pck.qnt_saltos++;

    // Bloquear a saída do roteador atual
    r[atual.x][atual.y].saida[direcao] = true;

}

void rede::desbloquear_saidas_rede() {
    for (vector<roteador> &vrot : r) {
        for(roteador &rot : vrot) {
            rot.desbloquear_saidas();
        }
    }
}

void rede::exclui_pacote(coord atual, int id) {
    for(int i=0; i < 4; ++i) {
        for(int j=0; j < r[atual.x][atual.y].entrada[i].size(); ++j) {
            if(r[atual.x][atual.y].entrada[i][j].id == id) {
                r[atual.x][atual.y].entrada[i].erase(r[atual.x][atual.y].entrada[i].begin() + j);
                return;
            }
        }
    }
}

void rede::aloca_pacote(pacote &pck, coord atual, int espaco) {
    r[atual.x][atual.y].entrada[espaco].push_back(pck);
}