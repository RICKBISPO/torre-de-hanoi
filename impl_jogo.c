#include "pilha.h"
#include "jogo.h"

void start_game(Pilha *pilha){

    init(&pilha[0]);
    init(&pilha[1]);
    init(&pilha[2]);

    for (int i = MAX_STACK_SIZE; i >= 1; i--){
        push(pilha[0], i);
    }
}

void start_buttons(Button buttons[]){
    // cria os 3 primeiros botoes que sao referentes as torres
    for (int i = 0; i < 3; i++){
        buttons[i] = (SDL_Rect){100 + i * 250, // x: horizontal em relacao a borda
                                320,           // y: vertical em relacao ao comeco do programa
                                100,           // w: largura do retangulo 
                                65};           // h: altura do retangulo 
    }

    // reiniciar jogo, desistir e fechar jogo
    buttons[3] = (SDL_Rect){82, 457, 140, 20};
    buttons[4] = (SDL_Rect){338, 457, 126, 20};
    buttons[5] = (SDL_Rect){568, 457, 178, 20};
}

void end_game(SDL_Window *window, SDL_Renderer *renderer, Pilha torres[]){
    // Limpar torres
    for (int i = 0; i < 3; i++){
        freePilha(&torres[i]);
    }

    // Fechar janela e limpar ponteiros
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void reset_game(Pilha torres[]){
    for (int i = 0; i < 3; i++){
        freePilha(&torres[i]);
    }

    start_game(torres);
}

void jogada(Pilha origem, Pilha destino){
    int temp;
    pop(origem, &temp);
    push(destino, temp);
}

bool verifica_acao(Pilha origem, Pilha destino){
    int topo_origem, topo_destino;

    if (!is_empty(origem) && !is_full(destino)){

        if (!is_empty(destino)){
            pop(destino, &topo_destino);
            push(destino, topo_destino);
        }
        else{
            topo_destino = topo_origem++;
        }

        pop(origem, &topo_origem);
        push(origem, topo_origem);

        if (topo_origem < topo_destino){
            return true;
        }
    }
    return false;
}

void jogada_aleatoria(SDL_Renderer *renderer, Pilha pilha[], int pausa){

    int origem, destino;
    int t1[MAX_STACK_SIZE];
    int t2[MAX_STACK_SIZE];
    int t3[MAX_STACK_SIZE];

    pilha_to_vetor(pilha[0], t1);
    pilha_to_vetor(pilha[1], t2);
    pilha_to_vetor(pilha[2], t3);
    
    while (!is_full(pilha[2])){

        origem = rand() % 3;
        destino = rand() % 3;

        if (is_full(pilha[0]) || is_full(pilha[1])){

            int passos[7][2];

            if (is_full(pilha[0])){
                int temp[7][2] = {{0, 2}, {0, 1}, {2, 1}, {0, 2}, {1, 0}, {1, 2}, {0, 2}};
                memcpy(passos, temp, sizeof(temp));
            }
            else if (is_full(pilha[1])){
                int temp[7][2] = {{1, 2}, {1, 0}, {2, 0}, {1, 2}, {0, 1}, {0, 2}, {1, 2}};
                memcpy(passos, temp, sizeof(temp));
            }

            for (int i = 0; i < 7; i++){
                origem = passos[i][0];
                destino = passos[i][1];

                jogada(pilha[origem], pilha[destino]);
                to_print_torres(renderer, pilha, pausa);
                SDL_RenderPresent(renderer);
            }
        }

        else if(t1[0] == 2 && t1[1] == 3){
            destino = 0;

            if (t2[0] == 1)
                origem = 1;
            else
                origem = 2;
        }

        else if(t2[0] == 2 && t2[1] == 3){
            destino = 1;

            if (t1[0] == 1)
                origem = 0;
            else
                origem = 2;
        }

        else if (t3[1] == 3){
            destino = 2;

            if (t1[0] == 1)
                origem = 0;
            else
                origem = 1;
        }

        else if ((t3[0] == 3) && origem == 2){
            continue;
        }

        if (verifica_acao(pilha[origem], pilha[destino]) && !is_full(pilha[2])){

            jogada(pilha[origem], pilha[destino]);
            to_print_torres(renderer, pilha, pausa);
        }
    }
}

void to_print_torres(SDL_Renderer *renderer, Pilha torres[], int pausa) {

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

void pilha_to_vetor(Pilha pilha, int array[]) {

    if (!is_empty(pilha)){
        int count = 0;
        Tipo_Informacao temp;
        Pilha aux;
        init(&aux);

        // enquanto a pilha nao estiver vazia
        // guarda no array e depois guarda em aux
        while (!is_empty(pilha)){
            pop(pilha, &temp);
            array[count] = temp;
            count += 1;
            push(aux, temp);
        }

        // coloca de aux na pilha
        while (!is_empty(aux)){
            pop(aux, &temp);
            push(pilha, temp);
        }
        freePilha(&aux);
    }
}

void to_print_botoes(SDL_Renderer *renderer, Button botoes[]){
    for (int i = 0; i < 6; i++){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); 
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
        SDL_RenderFillRect(renderer, &botoes[i]);
    }
}