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

void print_number_with_two_digits(ostream &os, int n) {
    if(n < 10) os << "0";
    os << n;
}

void print_upper_line(ostream &os, const vector<pacote>& pkg, bool saida) {
    os << " _ ";
    int size = pkg.size();
    for(int i=0; i < size; ++i) {
        print_number_with_two_digits(os, pkg[i].id);
        os << " _ ";
    }
    for(int i=size; i < 4; ++i) {
        os << "XX _";
        if(i != 3){
            os << " ";
        }
    }
    if(saida) os << "V_ \n";
    else os << "F_ \n";
}

void print_lower_line(ostream &os, const vector<pacote>& pkg, bool saida) {
    os << "|_ ";
    int size = pkg.size();
    for(int i=0; i < size; ++i) {
        print_number_with_two_digits(os, pkg[i].id);
        os << " _ ";
    }
    for(int i=size; i < 4; ++i) {
        os << "XX _";
        if(i != 3){
            os << " ";
        }
    }
    if(saida) os << "V_|\n";
    else os << "F_|\n";
}