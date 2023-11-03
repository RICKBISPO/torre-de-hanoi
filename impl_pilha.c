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

    printf("\033[H\033[J");

    for (int i = MAX_STACK_SIZE - 1; i >= 0; i--) {

        for (int j = 0; j < 3; j++) {
            int temp = torres[j]->itens[i];

            if ((temp != 3) && (temp != 2) && (temp != 1)) {
                printf("  |  ");
            } else{
                complemento_to_print(temp);
            }
            if (j < 2) {
                printf("\t");
            }
        }
        printf("\n");
    }
    printf("\n");

    #ifdef _WIN32
    Sleep(400); // No Windows
    #else
        usleep(400000); //  (Linux)
    #endif

}

void complemento_to_print(int valor) {
    if (valor == 1) printf("  #  ");
    else if (valor == 2) printf(" # # ");
    else if (valor == 3) printf("# # #");
}


void to_print_todas_sdl(SDL_Renderer *renderer, Pilha torres[]) {
    
    // define render com uma cor
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int x_base = 100; // Posição inicial X da primeira torre
    int y_base = 400; // Posição inicial Y da base das torres
    int torre_spacing = 250; // Espaçamento entre torres
    int disk_height = 20; // Altura dos discos

    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        
        int x_torre = x_base + i * torre_spacing;

        for (int j = 0; j < MAX_STACK_SIZE; j++) {

            int disco = torres[i]->itens[j];
            int y_disco = y_base - j * disk_height;
            
            // Desenhe o disco (#)
            if (disco == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Cor vermelha
                SDL_Rect rect = {x_torre - 20, y_disco - 10, 40, 20};
                SDL_RenderFillRect(renderer, &rect);
            } else if (disco == 2) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Cor verde
                SDL_Rect rect = {x_torre - 30, y_disco - 10, 60, 20};
                SDL_RenderFillRect(renderer, &rect);
            } else if (disco == 3) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Cor azul
                SDL_Rect rect = {x_torre - 40, y_disco - 10, 80, 20};
                SDL_RenderFillRect(renderer, &rect);
            }
            else {
                // Desenhe a haste (|)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Cor azul
                SDL_Rect rect = {x_torre - 2.5, y_disco - 10, 5, 20};
                SDL_RenderFillRect(renderer, &rect);
            } 
        }
    }

    
    SDL_Delay(1000);
    SDL_RenderPresent(renderer);

}


void pilha_to_vetor(Pilha pilha, int* array, int size) {

    if (!is_empty(pilha)){
        for (int i = 0; i < size; i++){
            int temp = pilha->itens[pilha->topo - i];

            if ((temp != 3) || (temp != 2) || (temp != 1)){
                array[i] = pilha->itens[pilha->topo - i];
            }else{
                array[i] = 0;
            }
        }
    }
}