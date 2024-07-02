#include "roteador.h"

int roteador::direcao(coord atual, coord destino) {
    coord dif = destino - atual;
    if(dif.x == 0) {
        if(dif.y > 0) return 0; // direita
        return 2; // esquerda
    }
    if(dif.x > 0) return 1; // baixo
    return 3; // cima
}

void roteador::desbloquear_saidas() {
    for(int i=0; i < 4; ++i) {
        saida[i] = false;
    }
}