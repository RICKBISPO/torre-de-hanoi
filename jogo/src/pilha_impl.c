#include "../include/pilha.h"

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

void free_pilha(Pilha* pilha){
    if (*pilha != NULL) {
        free(*pilha);
        *pilha = NULL; 
    }
}

// IMPLEMENTACAO DE PILHA USANDO LISTA SIMPLESMENTE ENCADEADA
// #include "../include/pilha.h"

// typedef struct node* Node;

// struct node{
// 	Tipo_Informacao info;
// 	Node next;
// };

// struct stack{
// 	Node topo;
// 	int total;
// };

// void init(Pilha* pilha){
// 	*pilha = malloc(sizeof(struct stack));
// 	(*pilha)->topo = NULL;
// 	(*pilha)->total = 0;
// }

// bool is_full(Pilha pilha){
// 	return pilha->total == MAX_STACK_SIZE;
// }

// bool is_empty(Pilha pilha){
// 	return pilha->topo == NULL;
// }

// bool push(Pilha pilha, Tipo_Informacao elemento){
// 	if (pilha != NULL){
		
// 		Node novo = malloc(sizeof(struct node));
// 		novo->info = elemento;

// 		novo->next = pilha->topo;
// 		pilha->topo = novo;

// 		pilha->total += 1;
// 		return true;
// 	}
// 	return false;
// }

// bool pop(Pilha pilha, Tipo_Informacao* elemento){
// 	if (pilha != NULL){
// 		if (!is_empty(pilha)){
			
// 			Node rip = pilha->topo;
// 			*elemento = rip->info;

// 			pilha->topo = rip->next;
			
// 			free(rip);

// 			pilha->total -= 1;
// 			return true;
// 		}
// 	}
// 	return false;
// }

// void free_pilha(Pilha* pilha){
//     if (*pilha != NULL) {
//         free(*pilha);
//         *pilha = NULL; 
//     }
// }