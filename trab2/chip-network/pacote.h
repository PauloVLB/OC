#ifndef PACOTE_H
#define PACOTE_H

#include <iostream>
#include <stack>
#include <map>
#include <queue>
#include "coord.h"
#include "rede.h"

using namespace std;

class rede;

class pacote {
    private: 
        vector<coord> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        map<coord, char> dir_str = {{dirs[0], 'B'}, {dirs[1], 'D'}, {dirs[2], 'C'}, {dirs[3], 'E'}};
    public:
        coord orig, dest, atual;
        
        int id;
        int tempo_init = 0;
        int tempo_final;
        int qnt_saltos = 0;
        int info;
        
        string caminho_final;
        stack<coord> caminho;        
    
        pacote() {}
        pacote(coord o, coord d, int i, int inf) : orig{o}, dest{d}, id{i}, info{inf}, atual{o} {}
        pacote(coord o, coord d, int i, int inf, int t) : orig{o}, dest{d}, id{i}, info{inf}, tempo_init{t}, atual{o} {}

        bool chegou();
        void bfs(rede &r);
        void decida(rede &r);
};







#endif