#include <bits/stdc++.h>
#include "coord.h"
#include "pacote.h"
#include "rede.h"
#include "instancia.h"

using namespace std;

#define MAX_TEMPO 10


int main() {
    int qnt_inst; cin >> qnt_inst;

    vector<instancia> instancias;
    while(qnt_inst--) {
        int tempo; cin >> tempo;
        int ox, oy, dx, dy; cin >> ox >> oy >> dx >> dy;


        int qnt_pacotes; cin >> qnt_pacotes;

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
    int id_atual = 0;
    for(int t = 0; t < MAX_TEMPO; t++) {

        cout << "Tempo " << t << ":\n";
        
        for(instancia &inst : instancias) {
            if(inst.tempo > t) break; // se ainda nao chegou sua hora
            if(!inst.tem_pacote()) continue; // se ja enviou todos os pacotes
            // TODO: checar se pode criar o pacote antes de criar
            pacotes_ativos.push_back(inst.criar_pacote(id_atual++, t));
        }

        for(pacote &p : pacotes_ativos) {
            cout << "Pacote " << p.id << ":\n";
            if(p.chegou()) {
                cout << "Já chegou\n";
                continue;
            }
            cout << "Não chegou ainda, vou calcular caminho ou executar proxima instrução no caminho atual\n";

            p.decida(red);
        }
    }


}