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
            pilha->topo -= 1;
            deuCerto = true;
        }
    }
    return deuCerto;
}

void to_print_todas(Pilha torres[]) {
    
    for (int i = 0; i < 3; i++) {
        printf("Torre %d\n", i + 1);
        for (int j = 2; j >= 0; j--) {
            if (j <= torres[i]->topo) {
                complemento_to_print(torres[i]->itens[j]);
            }else {
                printf("  |  \n");
            }
        }
        for (int i = 0; i < 5; i++){
            printf("\xE2\x80\xBE");
        }
        printf("\n");
    }
    printf("\n");
}

void complemento_to_print(int valor) {
    if (valor == 1) printf("  #  \n");
    else if (valor == 2) printf(" # # \n");
    else if (valor == 3) printf("# # #\n");
}
