#include "pilha.h"
#include "jogo.h"

void start_game(Pilha torres[], Button buttons[]){

    // Botoes das torres
    for (int i = 0; i < 3; i++){
        init(&torres[i]);

        int x = 100 + i * 250;  // x: horizontal em relacao a borda
        int y = 320;            // y: vertical em relacao ao comeco do programa
        int w = 100;            // w: largura do retangulo 
        int h = 65;             // h: altura do retangulo 

        buttons[i] = (SDL_Rect){x, y, w, h}; 
    }

    // Reiniciar jogo, desistir e fechar jogo
    buttons[3] = (SDL_Rect){82, 457, 140, 20};
    buttons[4] = (SDL_Rect){338, 457, 126, 20};
    buttons[5] = (SDL_Rect){568, 457, 178, 20};
    
    for(int i = MAX_STACK_SIZE; i >= 1; i--){
        push(torres[0], i);
    }

}

void end_game(Pilha torres[], SDL_Surface* icon, SDL_Renderer *renderer, SDL_Window *window){

    // Limpar torres
    freePilha(&torres[0]);
    freePilha(&torres[1]);
    freePilha(&torres[2]);

    // Fechar janela e limpar ponteiros
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void reset_game(Pilha torres[], int* temp,  int* primeiro, int* contador){

    // Limpar torres
    freePilha(&torres[0]);
    freePilha(&torres[1]);
    freePilha(&torres[2]);

    for (int i = 0, j = MAX_STACK_SIZE; i < 3, j >= 1; i++, j--){
        init(&torres[i]);
        push(torres[0], j);
    }

    *contador = 0;
    *temp = 3;
    *primeiro = true;
    system(CLEAR_SCREEN);
    printf("\njogadas: %d\n", *contador);
}

int descobrir_click(Button buttons[]){
    int mouseX, mouseY, temp;
    SDL_GetMouseState(&mouseX, &mouseY);

    int achou = false;
    for (int i = 0; i < NRO_BUTTONS && !achou; i++){

        if (mouseX >= buttons[i].x && mouseX <= (buttons[i].x + buttons[i].w) &&
            mouseY >= buttons[i].y && mouseY <= (buttons[i].y + buttons[i].h)){
            temp = i;
            return temp;
        }
    }
    return -1;
}

void jogada(Pilha torres[], int temp,  int* primeiro, int* contador, int* origem, int* destino){

    printf("indice %d\n", temp);
    
    if (*primeiro == true){
        *origem = temp;
        *primeiro = false;
    }
    else{
        *destino = temp;
        *primeiro = true;

        if (fazer_jogada(torres[*origem], torres[*destino])){
            *contador = *contador + 1; 
        }
        system(CLEAR_SCREEN);
        printf("\njogadas: %d\n", *contador);
    }
}

bool fazer_jogada(Pilha origem, Pilha destino){
    int topo_origem, topo_destino;

    if (!is_empty(origem) && !is_full(destino)){

        if (!is_empty(destino)){
            pop(destino, &topo_destino);
            push(destino, topo_destino);
        }

        pop(origem, &topo_origem);
        push(origem, topo_origem);

        if (topo_origem < topo_destino || is_empty(destino)){

            int temp;
            pop(origem, &temp);
            push(destino, temp);

            return true;
        }
    }
    return false;
}

void jogada_aleatoria(SDL_Renderer *renderer, Pilha torres[], int pausa){

    int origem, destino;
    int t1[MAX_STACK_SIZE];
    int t2[MAX_STACK_SIZE];
    int t3[MAX_STACK_SIZE];

    pilha_to_vetor(torres[TORRE_1], t1);
    pilha_to_vetor(torres[TORRE_2], t2);
    pilha_to_vetor(torres[TORRE_3], t3);
    
    while (!is_full(torres[TORRE_3])){

        // Se a torre 1 ou 2 estiverem cheias, aplica-se o gabarito de 7 passos
        if (is_full(torres[TORRE_1]) || is_full(torres[TORRE_2])){
            gabarito_torre(renderer, torres, pausa);
        }
        else if (!is_full(torres[TORRE_3]))
        {
            origem = rand() % 3;
            destino = rand() % 3;

            // funcao que diminui o numero de jogadas aleatorias por meio de algumas verificacoes
            diminuir_jogadas(t1, t2, t3, &origem, &destino);

            if (fazer_jogada(torres[origem], torres[destino]) && !is_full(torres[TORRE_3])){
                to_print_torres(renderer, torres, pausa);
                SDL_RenderPresent(renderer);
            }
        }
    }
}

void gabarito_torre(SDL_Renderer *renderer, Pilha torres[], int pausa){
    int passos[7][2];

    if (is_full(torres[0])){
        int temp[7][2] = {{0, 2}, {0, 1}, {2, 1}, {0, 2}, {1, 0}, {1, 2}, {0, 2}};
        memcpy(passos, temp, sizeof(temp));
    }
    else if (is_full(torres[1])){
        int temp[7][2] = {{1, 2}, {1, 0}, {2, 0}, {1, 2}, {0, 1}, {0, 2}, {1, 2}};
        memcpy(passos, temp, sizeof(temp));
    }

    for (int i = 0; i < 7; i++){
        int origem = passos[i][0];
        int destino = passos[i][1];

        fazer_jogada(torres[origem], torres[destino]);
        to_print_torres(renderer, torres, pausa);
        SDL_RenderPresent(renderer);
    }
}

void diminuir_jogadas(int torre1[], int torre2[], int torre3[], int* origem, int* destino){

    // Completa a primeira torre para em seguida executar o gabarito
    
    if(torre1[SEGUNDO_DISCO] == 3){
        *destino = TORRE_1;
        *origem = torre2[PRIMEIRO_DISCO] == 1 ? TORRE_2 : TORRE_3;
    }
    
    // Completa a segunda torre para em seguida executar o gabarito
    else if(torre2[SEGUNDO_DISCO] == 3){
        *destino = TORRE_2;
        *origem = torre1[PRIMEIRO_DISCO] == 1 ? TORRE_1 : TORRE_3;
    }

    // Completa a terceira torre com o disco que falta
    else if (torre3[SEGUNDO_DISCO] == 3){
        *destino = TORRE_3;
        *origem = torre1[PRIMEIRO_DISCO] == 1 ? TORRE_1 : TORRE_2;
    }

    // Nao deixa tirar o disco 3 da torre 3
    else if(torre3[PRIMEIRO_DISCO] == 3 && *origem == TORRE_3){
        *origem = rand() % 2;
    }
}

void to_print_torres(SDL_Renderer *renderer, Pilha torres[], int pausa) {

    SDL_Texture *backgroundTexture = IMG_LoadTexture(renderer, "assets/att.png");
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    int x_base = 150; // Posição horizontal inicial
    int y_base = 370; // Posição vertical inicial
    int espacamento = 250; 
    int altura = 20; // Altura 

    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        int x_torre = x_base + i * espacamento;
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
        int cores_base[4] = {255, 255, 255, 255};
        desenhar_torre(renderer, x_torre, y_base + 10, 100, 5, cores_base);

        for (int i = 0; i < 3; i++){

            int y_disco = y_base - i * altura;
            int largura = 5, altura = 20;
            int cores[4] = {255, 255, 255, 255};

            desenhar_torre(renderer, x_torre, y_disco -10, 5, altura, cores);
        }  

        while (tamanho_pilha_temp > 0) {
            Tipo_Informacao disco;
            pop(pilha_temp, &disco);
            tamanho_pilha_temp--; // Atualize o tamanho da pilha temporária

            int y_disco = y_base - total * altura;

            // Desenhe o disco (#) com uma borda
            if (disco == 1) {
                int cores[4] = {255, 0, 0, 255}; 
                desenhar_torre(renderer, x_torre, y_disco -10, 40, altura, cores);
            } else if (disco == 2) {
                int cores[4] = {0, 255, 0, 255}; 
                desenhar_torre(renderer, x_torre, y_disco -10, 60, altura, cores);

            } else if (disco == 3) {
                int cores[4] = {0, 0, 255, 255}; 
                desenhar_torre(renderer, x_torre, y_disco -10, 80, altura, cores);
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
                    x - largura/2,      // posicao horizontal do disco (- largura/2 para ficar centralizado)
                    y,                  // posicao vertical do disco
                    largura,            // largura do disco
                    altura              // altura do disco
                    };
    SDL_RenderFillRect(renderer, &rect);

    // Desenhe a borda
    SDL_SetRenderDrawColor(renderer, (cores[0]/2), (cores[1]/2), (cores[2]/2), cores[3]);
    SDL_RenderDrawRect(renderer, &rect);
}

void pilha_to_vetor(Pilha torres, int array[]) {

    if (!is_empty(torres)){
        int count = 0;
        Tipo_Informacao temp;
        Pilha aux;
        init(&aux);

        // enquanto a pilha nao estiver vazia
        // guarda no array e depois guarda em aux
        while (!is_empty(torres)){
            pop(torres, &temp);
            array[count] = temp;
            count += 1;
            push(aux, temp);
        }

        // coloca de aux na pilha
        while (!is_empty(aux)){
            pop(aux, &temp);
            push(torres, temp);
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