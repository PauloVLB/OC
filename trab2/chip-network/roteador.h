#ifndef ROTEADOR_H
#define ROTEADOR_H

#include <vector>
#include "pacote.h"
#include "coord.h"

using namespace std;

class pacote;


// void print_middle_lines(ostream &os, vector<int> ids, bool saida) {
//     for(int i=0; i < 4; ++i) {
//         os << "|                       |\n";
//         int size = ids.size();
        
//         for(int j=0; j < size; ++j) {
//             os << "XX                     XX\n";
//         }
//         print_number_with_two_digits(os, ids[i]);
//         os << "                     XX\n";
//         os << "F                       F\n";
//         os << "|_ ";
//         print_number_with_two_digits(os, ids[i+4]);
//         os << " _ ";
//         print_number_with_two_digits(os, ids[i+5]);
//         os << " _ XX _ XX _";
//         if(saida) os << "V_|";
//         else os << "F_|";
//     }
// }

void print_number_with_two_digits(ostream &os, int n);

void print_upper_line(ostream &os, const vector<pacote>& pkg, bool saida, bool bloqueado);

void print_lower_line(ostream &os, const vector<pacote>& pkg, bool saida, bool bloqueado);

void print_middle_lines(ostream &os, const vector<pacote>& pkg1, const vector<pacote>& pkg2, int pos, bool bloqueado);

void print_full_block(ostream &os);

void print_side_block(ostream &os);

class roteador {
public:
    vector<pacote> entrada[4]; // entrada[i][j] -> pacote na posição j da entrada i
    bool saida[4];
    bool bloqueado = false;

    int direcao(coord atual, coord destino);
    void desbloquear_saidas();

    //  _ XX _ XX _ XX _ XX _F_ 
    // |                       |
    // 01                     XX
    // XX                     XX
    // XX                     XX
    // XX                     XX
    // |_ 05 _ 06 _ XX _ XX _V_|
    friend ostream& operator<<(ostream &os, const roteador &r) {
        print_upper_line(os, r.entrada[3], r.saida[3], r.bloqueado);
        os << "\n|                       |\n";
        print_middle_lines(os, r.entrada[2], r.entrada[0], 0, r.bloqueado);
        os << '\n';
        print_middle_lines(os, r.entrada[2], r.entrada[0], 1, r.bloqueado);
        os << '\n';
        print_middle_lines(os, r.entrada[2], r.entrada[0], 2, r.bloqueado);
        os << '\n';
        print_middle_lines(os, r.entrada[2], r.entrada[0], 3, r.bloqueado);
        os << '\n';
        print_lower_line(os, r.entrada[1], r.saida[1], r.bloqueado);
        os << '\n';
        return os;
    }
};



#endif