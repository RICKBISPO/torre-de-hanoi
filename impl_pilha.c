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

void to_print_todas(Pilha torres[]){
    for (int i = 0; i < 3; i++){
        printf("Torre %d\n", i+1);
        if (torres[i]->topo == -1){
            printf("  |  \n");
            printf("  |  \n");
            printf("  |  \n");
        }
        else if (torres[i]->topo == 0){
            printf("  |  \n");
            printf("  |  \n");
            complemento_to_print(torres[i]->itens[0]);
        }
        else if(torres[i]->topo == 1){
            printf("  |  \n");
            complemento_to_print(torres[i]->itens[1]);
            complemento_to_print(torres[i]->itens[0]);
        }
        else if(torres[i]->topo == 2){
            complemento_to_print(torres[i]->itens[2]);
            complemento_to_print(torres[i]->itens[1]);
            complemento_to_print(torres[i]->itens[0]);
        }
    }
    printf("\n");

}
void complemento_to_print(int valor){
    if (valor == 1) printf("  #  \n");
    else if(valor == 2) printf(" # # \n");
    else if (valor == 3) printf("# # #\n");
}

Tipo_Informacao get_info(Pilha pilha)
{
    return pilha->itens[pilha->topo];
}