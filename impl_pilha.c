#include "pilha.h"

struct stack{
    Tipo_Informacao itens[MAX_STACK_SIZE];
    int topo;
};

void init(Pilha *pilha){

    *pilha = malloc(sizeof(struct stack));

    if (*pilha != NULL){
        (*pilha)->topo = -1;
    }
}

bool is_full(Pilha pilha){
    return (pilha->topo == MAX_STACK_SIZE - 1);
}

bool is_empty(Pilha pilha){
    return (pilha->topo == -1);
}

bool push(Pilha pilha, Tipo_Informacao elemento){
    bool deuCerto = false;

    if (pilha != NULL){
        if (!is_full(pilha)){
            pilha->topo += 1;
            pilha->itens[pilha->topo] = elemento;
            deuCerto = true;
        }
    }
    return deuCerto;
}

bool pop(Pilha pilha, Tipo_Informacao *elemento){
    bool deuCerto = false;

    if (pilha != NULL){
        if (!is_empty(pilha)){
            *elemento = pilha->itens[pilha->topo];
            pilha->itens[pilha->topo] = 0;
            pilha->topo -= 1;
            deuCerto = true;
        }
    }
    return deuCerto;
}

void to_print_todas(Pilha torres[]) {

    /**
     * Primeiro for vai rodar 3 vezes, mas com algumas mudanças
     * para que esse for possa servir para acessar os itens
     * da pilha
    */
    for (int i = MAX_STACK_SIZE - 1; i >= 0; i--) {

        /**
         * O segundo for pega as 3 linhas referentes as 3 linhas 
         * de cada pilha
        */
        for (int j = 0; j < 3; j++) {
            int temp = torres[j]->itens[i];

            /**
             * se temp nao for nenhum dos discos, ele exibe 
             * uma parte vazia
             * */ 
            if (temp != 3 & temp != 2 & temp != 1) {
                printf("  |  ");
            } else{
                complemento_to_print(temp); //Se nao, ele exibe os '#' conforme o tamanho do disco
            }

            // se j for menor que 2, ele exibe um 'tab' no console
            if (j < 2) {
                printf("\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}


void complemento_to_print(int valor) {
    if (valor == 1) printf("  #  ");
    else if (valor == 2) printf(" # # ");
    else if (valor == 3) printf("# # #");
}


void pilha_to_vetor(Pilha pilha, int* array, int size) {

    if (!is_empty(pilha)){
        for (int i = 0; i < size; i++){
            int temp = pilha->itens[pilha->topo - i];

            if (temp != 3 || temp != 2 || temp != 1){
                array[i] = pilha->itens[pilha->topo - i];
            }else{
                array[i] = 0;
            }
        }
    }
}

