#include "pacote.h"

using namespace std;

bool pacote::chegou() {
    return atual == dest;
}

void pacote::bfs(rede &r) {
    map<coord, bool> vis;
    map<coord, coord> antes;
    queue<coord> q;

    q.push(atual);
    vis[atual] = true;
    
    bool cheguei = false;
    while(!q.empty()) {
        coord f = q.front(); q.pop();

        if(f == dest) {
            cheguei = true;
            break;
        }

        for(coord dir : dirs) {
            coord proxima = f + dir;
        
            if(r.pode_ir(f, proxima) && !vis[proxima]) {                    
                q.push(proxima);
                antes[proxima] = f;
                vis[proxima] = true;
            }
        }
    }

    if(cheguei) {
        coord c = dest;
        while(c != atual) {
            caminho.push(c - antes[c]);
            c = antes[c];
        }
    }
}


void pacote::decida(rede &r) {
    if(caminho.empty()) {
        // TODO: ver se tem q esperar
        // limpa o caminho atual e faz bfs dnv
        cout << "Calculando rota..\n";
        bfs(r);

        stack<coord> caminho_aux = caminho;
        while(!caminho_aux.empty()) {
            // mostre a direção que vai tomar
            coord proxima_dir = caminho_aux.top(); caminho_aux.pop();
            cout << proxima_dir.x << " " << proxima_dir.y << endl;
        }
    } 
    
    if(caminho.empty()) {
        // Algoritmo XY
        coord dif = dest - atual;
        vector<coord> possibilidades;
        if(dif.y > 0) {
            possibilidades.push_back({0, 1}); // direita
        }
        if(dif.y < 0) {
            possibilidades.push_back({0, -1}); // esquerda
        }
        if(dif.x > 0) {
            possibilidades.push_back({1, 0}); // baixo
        } 
        if(dif.x < 0){
            possibilidades.push_back({-1, 0}); // cima
        }

        coord proxima_dir = {-1, -1};

        cout << "Possibilidades: \n";
        for(coord dir : possibilidades) {
            
            cout << dir.x << " " << dir.y << endl;

            coord proxima_coord = atual + dir;
            if(r.pode_ir(atual, proxima_coord)) {
                proxima_dir = dir;
                break;
            }
        }

        cout << "Executando instrução XY: \n";
        if(proxima_dir == coord{-1, -1}) {
            cout << "Nao pode ir para nenhuma direção\n";
            return;
        }

        cout << proxima_dir.x << " " << proxima_dir.y << endl;
        r.atualiza(*this, atual, atual + proxima_dir);
    }
    else {

        coord proxima_dir = caminho.top();
        coord proxima_coord = atual + proxima_dir;
        
        cout << "Executando proxima instrução: ";
        cout << proxima_dir.x << " " << proxima_dir.y << endl;

        if(r.pode_ir(atual, proxima_coord)) {
            caminho.pop();
            r.atualiza(*this, atual, proxima_coord);
        } else {
            cout << "o mano nao podia ir" << endl;
        }
    }
    
}