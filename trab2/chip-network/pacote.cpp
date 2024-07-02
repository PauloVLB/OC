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


//  _ _ _ _ _ _       _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _ 
// |           |     |           |   |           |   |           |   |           |   |           |   |           |   |           |
// F           |     F           |   F           |   F           |   F           |   F           |   F           |   F           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// 1           |     1           |   1           |   1           |   1           |   1           |   1           |   1           |
// |_ _ _ _ _ _|     |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|
//  _ _ _ _ _ _       _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _ 
// |           |     |           |   |           |   |           |   |           |   |           |   |           |   |           |
// F           |     F           |   F           |   F           |   F           |   F           |   F           |   F           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// 1           |     1           |   1           |   1           |   1           |   1           |   1           |   1           |
// |_ _ _ _ _ _|     |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|
//  _ _ _ _ _ _       _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _ 
// |           |     |           |   |           |   |           |   |           |   |           |   |           |   |           |
// F           |     F           |   F           |   F           |   F           |   F           |   F           |   F           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// 1           |     1           |   1           |   1           |   1           |   1           |   1           |   1           |
// |_ _ _ _ _ _|     |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|
//  _ _ _ _ _ _       _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _ 
// |           |     |           |   |           |   |           |   |           |   |           |   |           |   |           |
// F           |     F           |   F           |   F           |   F           |   F           |   F           |   F           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// 1           |     1           |   1           |   1           |   1           |   1           |   1           |   1           |
// |_ _ _ _ _ _|     |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|
//  _ _ _ _ _ _       _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _ 
// |           |     |           |   |           |   |           |   |           |   |           |   |           |   |           |
// F           |     F           |   F           |   F           |   F           |   F           |   F           |   F           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// 1           |     1           |   1           |   1           |   1           |   1           |   1           |   1           |
// |_ _ _ _ _ _|     |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|
//  _ _ _ _ _ _       _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _ 
// |           |     |           |   |           |   |           |   |           |   |           |   |           |   |           |
// F           |     F           |   F           |   F           |   F           |   F           |   F           |   F           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// 1           |     1           |   1           |   1           |   1           |   1           |   1           |   1           |
// |_ _ _ _ _ _|     |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|
//  _ _ _ _ _ _       _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _ 
// |           |     |           |   |           |   |           |   |           |   |           |   |           |   |           |
// F           |     F           |   F           |   F           |   F           |   F           |   F           |   F           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// 1           |     1           |   1           |   1           |   1           |   1           |   1           |   1           |
// |_ _ _ _ _ _|     |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|
//  _ _ _ _ _ _       _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _     _ _ _ _ _ _ 
// |           |     |           |   |           |   |           |   |           |   |           |   |           |   |           |
// F           |     F           |   F           |   F           |   F           |   F           |   F           |   F           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// X           |     X           |   X           |   X           |   X           |   X           |   X           |   X           |
// 1           |     1           |   1           |   1           |   1           |   1           |   1           |   1           |
// |_ _ _ _ _ _|     |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|   |_ _ _ _ _ _|

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
        //! Pode ser que o caminho esteja vazio aqui !//
        // XY
        // J . . . . H -> H . . .
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