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

void to_print_todas_sdl(SDL_Renderer *renderer, Pilha torres[], int pausa) {

    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "assets/att.png");
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    int x_base = 150; // Posição horizontal
    int y_base = 370; // Posição vertical
    int torre_spacing = 250; // Espaçamento
    int disk_height = 20; // Altura 

    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        int x_torre = x_base + i * torre_spacing;
        int tamanho_pilha_temp = 0;
        int total = 0;

        Pilha pilha_temp;
        init(&pilha_temp);

        // Copie os discos da torre original para a pilha temporária
        while (!is_empty(torres[i])) {
            Tipo_Informacao disco;
            pop(torres[i], &disco);
            push(pilha_temp, disco);
            tamanho_pilha_temp++; // Atualize o tamanho da pilha temporária
        }

        // Imprime base
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Cor Branca
        SDL_Rect rect = {x_torre - 50, y_base + 10, 100, 5};
        SDL_RenderFillRect(renderer, &rect);

        for (int i = 0; i < 3; i++){

            int y_disco = y_base - i * disk_height;
            int largura = 5, altura = 20;
            int cores[4] = {255, 255, 255, 255};

            desenhar_torre(renderer, x_torre, y_disco, 5, disk_height, cores);
        }  

        while (tamanho_pilha_temp > 0) {
            Tipo_Informacao disco;
            pop(pilha_temp, &disco);
            tamanho_pilha_temp--; // Atualize o tamanho da pilha temporária

            int y_disco = y_base - total * disk_height;

            // Desenhe a base (_)
            if (total == 0){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Cor Branca
                SDL_Rect rect = {x_torre - 50, y_disco + 10, 100, 5};
                SDL_RenderFillRect(renderer, &rect);
            }

            // Desenhe o disco (#) com uma borda
            if (disco == 1) {
                int cores[4] = {255, 0, 0, 255}; 
                desenhar_torre(renderer, x_torre, y_disco, 40, disk_height, cores);
            } else if (disco == 2) {
                int cores[4] = {0, 255, 0, 255}; 
                desenhar_torre(renderer, x_torre, y_disco, 60, disk_height, cores);

            } else if (disco == 3) {
                int cores[4] = {0, 0, 255, 255}; 
                desenhar_torre(renderer, x_torre, y_disco, 80, disk_height, cores);
            }

            // Empilhe de volta o disco na pilha original
            push(torres[i], disco);
            total++;
        }

        freePilha(&pilha_temp);
    }

    if (pausa == true) {
        SDL_Delay(400);
    }

    SDL_DestroyTexture(backgroundTexture);
}

void desenhar_torre(SDL_Renderer *renderer, int x, int y, int largura, int altura, int cores[]){


    SDL_SetRenderDrawColor(renderer, cores[0], cores[1], cores[2], cores[3]); 
    SDL_Rect rect = {
                    x - largura/2,  // posicao horizontal do disco (- largura/2 para ficar centralizado)
                    y - 10,         // posicao vertical do disco
                    largura,        // largura do disco
                    altura          // altura do disco
                    };
    SDL_RenderFillRect(renderer, &rect);

    // Desenhe a borda
    SDL_SetRenderDrawColor(renderer, (cores[0]/2), (cores[1]/2), (cores[2]/2), cores[3]); // Azul escuro rgba(2, 2, 112, 255)
    SDL_RenderDrawRect(renderer, &rect);
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
