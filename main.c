#include "pilha.h"
#define MAX_DISCO 3

void start_game(Pilha pilha[]);
void jogada(Pilha pilha[], int pega, int coloca);
bool verifica_acao(Pilha pilha_pega, Pilha pilha_coloca);

int main(void)
{
    // Limpa o console
    system("cls");

    Pilha pilha[3];
    int pega, coloca, desistir;

    start_game(pilha);
    to_print_todas(pilha);

    do{
        printf("Deseja desistir? 1-Sim/2-Nao: ");
        scanf("%d", &desistir);

        if (desistir != 1){
            printf("Escolha uma pilha para retirar e uma para colocar\n");
            printf("0: p1 || 1: p2 || 2: p3\n");
            scanf("%d%d", &pega, &coloca);

            system("cls");

            jogada(pilha, pega, coloca);
            to_print_todas(pilha);
        }
    } while (!is_full(pilha[2]) && desistir != 1);

    if (desistir != 1){
        system("cls");
        printf("Voce ganhou!!!!\n\n");
        to_print_todas(pilha);
    }else{
        printf("Voce desistiu!\n");
    }
    
    return 0;
}

void start_game(Pilha pilha[]){
    for (int i = 0; i < MAX_STACK_SIZE; i++){
        init(&pilha[i]);
    }

    for (int i = MAX_DISCO; i >= 1; i--){
        push(pilha[0], i);
    }
}

void jogada(Pilha pilha[], int pega, int coloca){
 
    if (verifica_acao(pilha[pega], pilha[coloca])){
        int temp;
        pop(pilha[pega], &temp);
        push(pilha[coloca], temp);
    }else{
        printf("Acao nao permitida!\n\n\n");
    }
}

bool verifica_acao(Pilha pilha_pega, Pilha pilha_coloca){
    int resultado = false;

    if (!is_empty(pilha_pega) && !is_full(pilha_coloca)){
        if (get_info(pilha_pega) < get_info(pilha_coloca)){
            resultado = true;
        }
    }
    return resultado;
}