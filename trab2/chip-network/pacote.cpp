#include "pacote.h"

using namespace std;

bool pacote::chegou() {
    return atual == dest;
}

void pacote::bfs(const rede &r) {
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
        
            if(r.pode_ir(proxima) && !vis[proxima]) {                    
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
    coord proxima_dir = caminho.top();
    coord proxima_coord = atual + proxima_dir;

    if(r.pode_ir(proxima_coord)) {
        caminho.pop();
        r.atualiza(id, atual, proxima_coord);
        atual = proxima_coord;
        qnt_saltos++;
    } else {
        // TODO: ver se tem q esperar
        // limpa o caminho atual e faz bfs dnv
        while(!caminho.empty()) caminho.pop();
        bfs(r);
    }
}