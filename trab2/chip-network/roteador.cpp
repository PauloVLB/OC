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

void print_full_block(ostream &os) {
    for(int i=0; i < 23; ++i) {
        os << "X";
    }
}

void print_side_block(ostream &os) {
    os << "XX";
    for(int i=0; i < 19; ++i) {
        os << " ";
    }
    os << "XX";
}

void print_upper_line(ostream &os, const vector<pacote>& pkg, bool saida, bool bloqueado) {
    if(bloqueado) {
        print_full_block(os);
        return;
    }
    os << " _ ";
    int size = pkg.size();
    for(int i=0; i < size; ++i) {
        print_number_with_two_digits(os, pkg[i].id);
        os << " _ ";
    }
    for(int i=size; i < 4; ++i) {
        os << ".. _";
        if(i != 3){
            os << " ";
        }
    }
    os << " ";
}

void print_lower_line(ostream &os, const vector<pacote>& pkg, bool saida, bool bloqueado) {
    if(bloqueado) {
        print_full_block(os);
        return;
    }
    os << "|_ ";
    int size = pkg.size();
    for(int i=0; i < size; ++i) {
        print_number_with_two_digits(os, pkg[i].id);
        os << " _ ";
    }
    for(int i=size; i < 4; ++i) {
        os << ".. _";
        if(i != 3){
            os << " ";
        }
    }
    os << "|";
}

void print_middle_lines(ostream &os, const vector<pacote>& pkg1, const vector<pacote>& pkg2, int pos, bool bloqueado) {
    if(bloqueado) {
        print_side_block(os);
        return;
    }
    if(pos < pkg1.size()) print_number_with_two_digits(os, pkg1[pos].id);
    else os << "..";
    os << "                   ";
    if(pos < pkg2.size()) print_number_with_two_digits(os, pkg2[pos].id);
    else os << "..";
}