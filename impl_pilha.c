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

void freePilha(Pilha* pilha){
    if (*pilha != NULL) {
        free(*pilha);
        *pilha = NULL; 
    }
}

void to_print_todas_sdl(SDL_Renderer *renderer, Pilha torres[]) {

    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "assets/1.png");

    if (backgroundTexture == NULL) {
        printf("Erro ao carregar a imagem de fundo: %s\n", SDL_GetError());
        // Lidar com o erro, se necessário.
    }

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    int x_base = 150; // Posição inicial X da primeira torre
    int y_base = 370; // Posição inicial Y da base das torres
    int torre_spacing = 250; // Espaçamento entre torres
    int disk_height = 20; // Altura dos discos

    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        
        int x_torre = x_base + i * torre_spacing;

        for (int j = 0; j < MAX_STACK_SIZE; j++) {

            int disco = torres[i]->itens[j];
            int y_disco = y_base - j * disk_height;

            // Desenhe a base (_)
            if (j == 0){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Cor Preta
                SDL_Rect rect = {x_torre - 50, y_disco + 10, 100, 5};
                SDL_RenderFillRect(renderer, &rect);
            }
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
            // Desenhe a haste (|)
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Cor Preta
                SDL_Rect rect = {x_torre - 2.5, y_disco - 10, 5, 20};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    // SDL_Delay(400);
    SDL_DestroyTexture(backgroundTexture);

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
