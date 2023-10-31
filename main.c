#include "pilha.h"
#include <time.h>
#include <unistd.h>

#define MAX_DISCO 3

void start_game(Pilha *pilha);
void jogada(Pilha origem, Pilha destino);
bool verifica_acao(Pilha origem, Pilha destino);
// void jogada_aleatoria(Pilha pilha[]);
// bool is_pilha3_correta(Pilha pilha);

int main(void)
{
    srand((unsigned int)time(NULL));

    Pilha pilha[3];
    int origem, destino, desistir;

    start_game(pilha);

    do{
        system("clear");
        to_print_todas(pilha);

        printf("Deseja desistir? 1-Sim/2-Nao: ");
        scanf("%d", &desistir);

        if (desistir != 1){
            printf("Escolha uma pilha para retirar e uma para colocar\n");
            printf("0: p1 || 1: p2 || 2: p3\n");
            scanf("%d%d", &origem, &destino);

            jogada(pilha[origem], pilha[destino]);
        }
    } while (!is_full(pilha[2]) && desistir != 1);

    if (desistir != 1){
        system("clear");
        printf("Voce ganhou!!!!\n");
        to_print_todas(pilha);
    }else{
        printf("Voce desistiu!\n");
        // jogada_aleatoria(pilha);
    }

    return 0;
}

void start_game(Pilha *pilha){
    
    //inicializa as 3 pilhas
    init(&pilha[0]);
    init(&pilha[1]);
    init(&pilha[2]);

    // Enche a primeira pilha com os discos
    for (int i = MAX_DISCO; i >= 1; i--){
        push(pilha[0], i);
    }
}



void jogada(Pilha origem, Pilha destino){
    // Se a funcao retornar true, tira de uma torre(indice pega) e 
    // coloca em outra(indice coloca)
    if (verifica_acao(origem, destino)){
        int temp;
        pop(origem, &temp);
        push(destino, temp);
    }
}

bool verifica_acao(Pilha origem, Pilha destino){

    int topo_origem;
    int topo_destino;

    // se origem nao estiver vazio e destino nao estiver cheio 
    if (!is_empty(origem) && !is_full(destino)){

        // Se destino nao estiver vazio
        if (!is_empty(destino)){
            // guarda o topo do destino
            pop(destino, &topo_destino);
            push(destino, topo_destino);  
        }
        
        // guarda o topo do origem
        pop(origem, &topo_origem);
        push(origem, topo_origem);
   
        // Se topo de origem for menor que topo de destino
        // OU destino for vazio
        // Retorna true
        if (topo_origem < topo_destino || is_empty(destino)){
            return true;
        }
    }
    return false;
}

// void jogada_aleatoria(Pilha pilha[]){

//     int temp1, temp2;

//     while (!is_full(pilha[2]))
//     {
//         system("clear");
//         to_print_todas(pilha);

//         temp1 = rand() % 3;
//         temp2 = rand() % 3;



//         jogada(pilha, temp1, temp2);
//     }

// }

// bool is_pilha3_correta(Pilha pilha) {


    
// }
