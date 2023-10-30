#include "pilha.h"
#define MAX_DISCO 3

void start_game(Pilha pilha[]);
void jogada(Pilha pilha[], int pega, int coloca);
bool verifica_acao(Pilha pega, Pilha coloca);

int main(void)
{
    Pilha pilha[3];
    int pega, coloca, desistir;

    start_game(pilha);

    do{
        system("cls");
        to_print_todas(pilha);

        printf("Deseja desistir? 1-Sim/2-Nao: ");
        scanf("%d", &desistir);

        if (desistir != 1){
            printf("Escolha uma pilha para retirar e uma para colocar\n");
            printf("0: p1 || 1: p2 || 2: p3\n");
            scanf("%d%d", &pega, &coloca);

            jogada(pilha, pega, coloca);
        }
    } while (!is_full(pilha[2]) && desistir != 1);

    if (desistir != 1){
        system("cls");
        printf("Voce ganhou!!!!\n");
        to_print_todas(pilha);
    }else{
        printf("Voce desistiu!\n");
    }

    return 0;
}

void start_game(Pilha pilha[]){
    
    //inicializa as 3 pilhas
    init(&pilha[0]);
    init(&pilha[1]);
    init(&pilha[2]);

    // Enche a primeira pilha com os discos
    for (int i = MAX_DISCO; i >= 1; i--){
        push(pilha[0], i);
    }
}

void jogada(Pilha pilha[], int pega, int coloca){
 
    // Se a funcao retornar true, tira de uma torre(indice pega) e 
    // coloca em outra(indice coloca)
    if (verifica_acao(pilha[pega], pilha[coloca])){
        int temp;
        pop(pilha[pega], &temp);
        push(pilha[coloca], temp);
    }else{
        printf("Acao nao permitida!\n\n\n");
    }
}

bool verifica_acao(Pilha pega, Pilha coloca){

    // Se a pilha que irá pegar nao esta vazia &&
    // se a pilha que vai colocar não está cheia
    if (!is_empty(pega) && !is_full(coloca))
    {
        // Se o valor do disco é menor do que o que está na pilha
        // que irá ser colocado
        if (get_info(pega) < get_info(coloca)){
            return true;
        }
    }
    return false;
}