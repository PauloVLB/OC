#include <bits/stdc++.h>
#include "coord.h"
#include "pacote.h"
#include "rede.h"
#include "instancia.h"

using namespace std;

#define MAX_TEMPO 10


int main() {
    int qnt_inst; cin >> qnt_inst;
    int qnt_total_pacotes = 0;


    vector<instancia> instancias;
    while(qnt_inst--) {
        int tempo; cin >> tempo;
        int ox, oy, dx, dy; cin >> ox >> oy >> dx >> dy;


        int qnt_pacotes; cin >> qnt_pacotes;
        qnt_total_pacotes += qnt_pacotes;

        vector<int> pacotes(qnt_pacotes);
        for(int &pac : pacotes) {
            cin >> pac;
        }

        instancias.push_back({tempo, {ox, oy}, {dx, dy}, pacotes});
    }

    int qnt_bloqueados; cin >> qnt_bloqueados;

    rede red;
    while(qnt_bloqueados--) {
        int x, y; cin >> x >> y;
        red.r[x][y].bloqueado = true;
    }

    sort(instancias.begin(), instancias.end());

    vector<pacote> pacotes_ativos;
    unordered_map<int, bool> pacotes_chegaram;
    int id_atual = 0;
    for(int t = 0; t < MAX_TEMPO; t++) {

        cout << "Tempo " << t << ":\n";
        
        // Checar se há instancias para criar pacotes
        for(instancia &inst : instancias) {
            if(inst.tempo > t) break; // se ainda nao chegou sua hora
            if(!inst.tem_pacote()) continue; // se ja enviou todos os pacotes
            // Checar se existe posição no roteador de origem para alocar um novo pacote
            bool tem_espaco = false;
            int espaco = -1;
            for(int i=3; i >= 0; --i) {
                if(red.r[inst.orig.x][inst.orig.y].entrada[i].size() < 4) {
                    tem_espaco = true;
                    espaco = i;
                    break;
                }
            }
            if(!tem_espaco) continue;
            pacotes_ativos.push_back(inst.criar_pacote(id_atual++, t, red, espaco));

        }
        // if(t == 0){
        //     // Vou printar o roteador 2 2
        //     cout << red.r[2][2];
        // }
        // if(t == 1){
        //     // Vou printar o roteador 2 2
        //     cout << red.r[2][2];
        // }

        // Realizar "movimentos" dos pacotes
        for(pacote &p : pacotes_ativos) {
            cout << "Pacote " << p.id << " (";
            cout << p.atual.x << " " << p.atual.y << "):\n";

            if(p.chegou()) {
                cout << "Já chegou\n";
                if(pacotes_chegaram.count(p.id)) continue;
                pacotes_chegaram[p.id] = true;
                red.exclui_pacote(p.atual, p.id);
                continue;
            }
            cout << "Não chegou ainda, vou calcular caminho ou executar proxima instrução no caminho atual\n";

            p.decida(red);
        }

        red.desbloquear_saidas_rede();

        // Checar se ainda há pacotes
        if(pacotes_chegaram.size() == qnt_total_pacotes) {
            cout << "Nada mais a fazer\n";
            break;
        }
    }


}