#include "pilha.h"

void start_game(Pilha *pilha){

    init(&pilha[0]);
    init(&pilha[1]);
    init(&pilha[2]);

    for (int i = MAX_STACK_SIZE; i >= 1; i--){
        push(pilha[0], i);
    }
}

void jogada(Pilha origem, Pilha destino){
    int temp;
    pop(origem, &temp);
    push(destino, temp);
}

bool verifica_acao(Pilha origem, Pilha destino){
    int topo_origem, topo_destino;

    if (!is_empty(origem) && !is_full(destino)){

        if (!is_empty(destino)){
            pop(destino, &topo_destino);
            push(destino, topo_destino);
        }
        else{
            topo_destino = topo_origem++;
        }

        pop(origem, &topo_origem);
        push(origem, topo_origem);

        if (topo_origem < topo_destino){
            return true;
        }
    }
    return false;
}

void jogada_aleatoria(SDL_Renderer *renderer, Pilha pilha[]){

    int origem, destino;
    int t1[MAX_STACK_SIZE];
    int t2[MAX_STACK_SIZE];
    int t3[MAX_STACK_SIZE];

    pilha_to_vetor(pilha[0], t1, MAX_STACK_SIZE);
    pilha_to_vetor(pilha[1], t2, MAX_STACK_SIZE);
    pilha_to_vetor(pilha[2], t3, MAX_STACK_SIZE);

    while (!is_full(pilha[2])){

        origem = rand() % 3;
        destino = rand() % 3;

        // Caso onde a Torre 1 ou 2 estão cheias,
        // conforme cada caso, ele executa uma matriz
        // que contém o gabarito

        if (is_full(pilha[0]) || is_full(pilha[1])){

            int passos[7][2];

            if (is_full(pilha[0])){
                int temp[7][2] = {{0, 2}, {0, 1}, {2, 1}, {0, 2}, {1, 0}, {1, 2}, {0, 2}};
                memcpy(passos, temp, sizeof(temp));
            }
            else if (is_full(pilha[1])){
                int temp[7][2] = {{1, 2}, {1, 0}, {2, 0}, {1, 2}, {0, 1}, {0, 2}, {1, 2}};
                memcpy(passos, temp, sizeof(temp));
            }

            for (int i = 0; i < 7; i++){
                origem = passos[i][0];
                destino = passos[i][1];

                jogada(pilha[origem], pilha[destino]);
                to_print_todas_sdl(renderer, pilha);
            }
        }

        // caso onde a torre 1 já tem o disco 3 e 2
        // o if acha o disco 1 e coloca ele encima dessa torre
        // após isso, no próximo while, ele irá entrar no primeiro if,
        // onde é torre 1 == full
        else if(t1[0] == 2 && t1[1] == 3){
            destino = 0;

            if (t2[0] == 1)
                origem = 1;
            else
                origem = 2;
        }

        // caso onde a torre 2 já tem o disco 3 e 2
        // o if acha o disco 1 e coloca ele encima dessa torre
        // após isso, no próximo while, ele irá entrar no primeiro if,
        // onde é torre 2 == full
        else if(t2[0] == 2 && t2[1] == 3){
            destino = 1;

            if (t1[0] == 1)
                origem = 0;
            else
                origem = 2;
        }

        // Se a torre 3 já estiver com os discos 2 e 3, ele acha o último disco
        // e coloca ele na torre 3
        else if (t3[1] == 3){
            destino = 2;

            if (t1[0] == 1)
                origem = 0;
            else
                origem = 1;
        }

        // Caso onde a torre 3 tem apenas o disco 3 e origem é essa torre
        // ele pula essa repeticao
        else if ((t3[0] == 3) && origem == 2){
            continue;
        }

        if (verifica_acao(pilha[origem], pilha[destino]) && !is_full(pilha[2])){

            jogada(pilha[origem], pilha[destino]);
            to_print_todas_sdl(renderer, pilha);
        }
    }
}