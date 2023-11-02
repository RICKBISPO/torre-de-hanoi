#include "pilha.h"
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void start_game(Pilha *pilha);
void jogada(Pilha origem, Pilha destino);
bool verifica_acao(Pilha origem, Pilha destino);
void jogada_aleatoria(Pilha pilha[]);

int main(void){

    srand((unsigned int)time(NULL));

    Pilha pilha[MAX_STACK_SIZE];
    int origem, destino, desiste = false;

    start_game(pilha);

    do{
        printf("\033[H\033[J");
        to_print_todas(pilha);

        printf("Escolha uma torre de origem e uma de destino:\n");
        printf("(1) torre 1 || (2) torre 2 || (3) torre 3\n");
        printf("Ou digite '0 0' para desistir\n");
        scanf("%d%d", &origem, &destino);

        if ((origem != 0) && (destino != 0)){

            origem--;
            destino--;

            if (verifica_acao(pilha[origem], pilha[destino])){
                jogada(pilha[origem], pilha[destino]);
            }
        }else{
            desiste = true;
        }

    } while (!is_full(pilha[2]) && !desiste);

    if (!desiste){
        printf("\033[H\033[J");
        printf("----Voce ganhou!----\n");
        to_print_todas(pilha);
    }
    else{
        jogada_aleatoria(pilha);
    }

    return 0;
}

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

    // se origem nao estiver vazio e destino nao estiver cheio
    if (!is_empty(origem) && !is_full(destino)){

        // Se destino nao estiver vazio
        if (!is_empty(destino))
        {
            // guarda o topo do destino
            pop(destino, &topo_destino);
            push(destino, topo_destino);
        }

        // guarda o topo do origem
        pop(origem, &topo_origem);
        push(origem, topo_origem);

        // Se topo de origem for menor que topo de destino
        // OU destino for vazio, retorna true, se nao retorna false
        if (topo_origem < topo_destino || is_empty(destino)){
            return true;
        }
    }
    return false;
}

void jogada_aleatoria(Pilha pilha[])
{
    int origem, destino;
    int temp[MAX_STACK_SIZE];

    // Enquanto a terceira pilha nao estiver cheia
    while (!is_full(pilha[2])){

        // cria dois randons que servirao de indice para as pilhas
        origem = rand() % 3;
        destino = rand() % 3;

        // passa a terceira pilha para dentro do vetor
        pilha_to_vetor(pilha[2], temp, MAX_STACK_SIZE);

        /**
         * Quando a terceira pilha possui apenas o disco 3,
         * o array[0] tem o valor de 3 se isso for verdade, 
         * ele pula para a próxima repeticao do while, não tirando essa peça do seu lugar
         * O mesmo acontece se (temp[0] == 2) && (temp[1] == 3)
         * isso diminui muito o tempo que o while leva para completar o jogo
        */

       if ((temp[0] == 3) && (origem == 2)){
            continue;
        }
        else if((temp[0] == 2) && (temp[1] == 3) && (origem == 2)){
            destino = 2;
            origem = rand() % 2;
            
        }

        /**
         * chama a funcao que verifica se a jogada pode ser feita
        */
        if (verifica_acao(pilha[origem], pilha[destino])){

            jogada(pilha[origem], pilha[destino]);

            printf("\033[H\033[J");

            to_print_todas(pilha);

            #ifdef _WIN32
                Sleep(400); // No Windows
            #else
                usleep(400000); //  (Linux)
            #endif
        }
    }
}
