#include "../include/jogo.h"

Game iniciar_jogo(){

    SDL_Init(SDL_INIT_EVERYTHING);

    Game jogo = malloc(sizeof(struct jogo));
    
    // Cria janela e renderizador
    jogo->window =  SDL_CreateWindow("Torre de Hanoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    jogo->renderer = SDL_CreateRenderer(jogo->window, -1, SDL_RENDERER_ACCELERATED);
    
    // Cria icone do jogo
    jogo->icon = SDL_LoadBMP("assets/images/icone.bmp");
    SDL_SetWindowIcon(jogo->window, jogo->icon);

    // Cria a fonte do jogo
    TTF_Init();
    jogo->font = TTF_OpenFont("assets/fonts/Our-Arcade-Games.ttf", 24);

    // inicializa as torres
    iniciar_torres(jogo->torres);
    
    // inicializa os botoes
    iniciar_botoes(jogo->buttons);

    // zera o contador
    jogo->contador = 0;
    jogo->status = JOGANDO;
    jogo->primeiro = true;

    return jogo;
}

void iniciar_torres(Pilha torres[]){

    for (int i = 0, j = 3; i < 3, j >= 1; i++, j--){
        init(&torres[i]);
        push(torres[0], j);
    }
}

void iniciar_botoes(Button buttons[]){

    for (int i = 0; i < 3; i++){
        int horizontal = 100 + i * 250, vertical = 320, largura = 100, altura = 65;

        buttons[i] = (SDL_Rect){horizontal, vertical, largura, altura};  
    }

    buttons[REINICIAR] = (SDL_Rect){82, 457, 140, 20};
    buttons[DESISTIR] = (SDL_Rect){338, 457, 126, 20};
    buttons[SAIR] = (SDL_Rect){568, 457, 178, 20};
}

void end_game(Game jogo){

    free_pilha(&(jogo->torres[TORRE_1]));
    free_pilha(&(jogo->torres[TORRE_2]));
    free_pilha(&(jogo->torres[TORRE_3]));

    // Fechar janela e limpar ponteiros
    SDL_FreeSurface(jogo->icon);
    SDL_DestroyRenderer(jogo->renderer);
    SDL_DestroyWindow(jogo->window);
    TTF_CloseFont(jogo->font);
    TTF_Quit();
    SDL_Quit();
    free(jogo);
}

void reset_game(Game jogo){

    // Limpar torres
    free_pilha(&(jogo->torres[TORRE_1]));
    free_pilha(&(jogo->torres[TORRE_2]));
    free_pilha(&(jogo->torres[TORRE_3]));

    iniciar_torres(jogo->torres);

    jogo->contador = 0;
    jogo->primeiro = true;
    jogo->status = JOGANDO;
    system(CLEAR_SCREEN);
    printf("\njogadas: %d\n", jogo->contador);
}

int descobrir_click(Game jogo){
    int resultado = -1;
    int achou = false;

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    for (int i = 0; i < NRO_BUTTONS && !achou; i++){

        if (mouseX >= jogo->buttons[i].x && mouseX <= (jogo->buttons[i].x + jogo->buttons[i].w) &&
            mouseY >= jogo->buttons[i].y && mouseY <= (jogo->buttons[i].y + jogo->buttons[i].h)){
            resultado = i;
            achou = true;
        }
    }
    return resultado;
}

void jogada(Game jogo, int temp){

    printf("indice %d\n", temp);
    
    if (jogo->primeiro == true){
        jogo->origem = temp;
        jogo->primeiro = false;
    }
    else{
        jogo->destino = temp;
        jogo->primeiro = true;

        if (fazer_jogada(jogo->torres[jogo->origem], jogo->torres[jogo->destino])){
            jogo->contador++;
        }
        system(CLEAR_SCREEN);
        printf("\njogadas: %d\n", jogo->contador);
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

void resolver_jogo(Game jogo){

    jogo->status = PERDEU;

    while (!is_full(jogo->torres[TORRE_3])){


        if (is_full(jogo->torres[TORRE_1]) || is_full(jogo->torres[TORRE_2])){
            gabarito_torre(jogo);
            break;
        }
        else{
            jogo->origem = rand() % 3;
            jogo->destino = rand() % 3;

            diminuir_jogada(jogo);

            if (fazer_jogada(jogo->torres[jogo->origem], jogo->torres[jogo->destino])){
                exibir_torres(jogo);
                SDL_RenderPresent(jogo->renderer);
            }
        }
    }
}

void gabarito_torre(Game jogo){

    int passos[7][2];

    if (is_full(jogo->torres[0])){
        int temp[7][2] = {{0, 2}, {0, 1}, {2, 1}, {0, 2}, {1, 0}, {1, 2}, {0, 2}};
        memcpy(passos, temp, sizeof(temp));
    }
    else if (is_full(jogo->torres[1])){
        int temp[7][2] = {{1, 2}, {1, 0}, {2, 0}, {1, 2}, {0, 1}, {0, 2}, {1, 2}};
        memcpy(passos, temp, sizeof(temp));
    }

    for (int i = 0; i < 7; i++){
        int origem = passos[i][0];
        int destino = passos[i][1];

        fazer_jogada(jogo->torres[origem], jogo->torres[destino]);
        exibir_torres(jogo);
        SDL_RenderPresent(jogo->renderer);
    }
}

void pilha_to_vetor(Pilha torres, int array[]) {

    if (!is_empty(torres)){
        int count = 0;
        Tipo_Informacao temp;
        Pilha aux;
        init(&aux);

        while (!is_empty(torres)){
            pop(torres, &temp);
            array[count] = temp;
            count += 1;
            push(aux, temp);
        }

        while (!is_empty(aux)){
            pop(aux, &temp);
            push(torres, temp);
        }
        free_pilha(&aux);
    }
}

void diminuir_jogada(Game jogo){

    int torre1[MAX_STACK_SIZE];
    int torre2[MAX_STACK_SIZE];
    int torre3[MAX_STACK_SIZE];

    pilha_to_vetor(jogo->torres[TORRE_1], torre1);
    pilha_to_vetor(jogo->torres[TORRE_2], torre2);
    pilha_to_vetor(jogo->torres[TORRE_3], torre3);

    // Completa a primeira torre para em seguida executar o gabarito
    if(torre1[PRIMEIRO_DISCO] == 2 && torre1[SEGUNDO_DISCO] == 3){
        jogo->destino = TORRE_1;
        jogo->origem = torre2[PRIMEIRO_DISCO] == 1 ? TORRE_2 : TORRE_3;
    }
    
    // Completa a segunda torre para em seguida executar o gabarito
    else if(torre1[PRIMEIRO_DISCO] == 2 && torre1[SEGUNDO_DISCO] == 3){
        jogo->destino = TORRE_2;
        jogo->origem = torre1[PRIMEIRO_DISCO] == 1 ? TORRE_1 : TORRE_3;
    }

    // Completa a terceira torre com o disco que falta
    else if (torre3[PRIMEIRO_DISCO] == 2 && torre3[SEGUNDO_DISCO] == 3){
        jogo->destino = TORRE_3;
        jogo->origem = torre1[PRIMEIRO_DISCO] == 1 ? TORRE_1 : TORRE_2;
    }

    // Se a configuracao do jogo ser: TORRE1: 3; TORRE2: 2; TORRE3: 1.
    else if(torre1[PRIMEIRO_DISCO] == 3 && torre2[PRIMEIRO_DISCO] == 2 && torre3[PRIMEIRO_DISCO] == 1){
        jogo->origem = TORRE_2;
        jogo->destino = TORRE_1;
    }
    
    // Se a configuracao do jogo ser: TORRE1: 3; TORRE2: 1; TORRE3: 2.
    else if(torre1[PRIMEIRO_DISCO] == 3 && torre2[PRIMEIRO_DISCO] == 1 && torre3[PRIMEIRO_DISCO] == 2){
        jogo->origem = TORRE_3;
        jogo->destino = TORRE_1;
    }

    // se a torre 1 tiver o disco 3 e a torre 3 tiver 1 e 2
    else if(torre1[PRIMEIRO_DISCO] == 3 && torre3[PRIMEIRO_DISCO] == 1 && torre3[SEGUNDO_DISCO] == 2){
        jogo->origem = TORRE_3;
        jogo->destino = TORRE_2;
    }

    // Nao deixa tirar o disco 3 da torre 3
    else if(torre3[PRIMEIRO_DISCO] == 3){
        jogo->origem = rand() % 2;
    }
}

void exibir_torres(Game jogo) {

    SDL_Texture *backgroundTexture;

    if (jogo->status == JOGANDO){
        backgroundTexture = IMG_LoadTexture(jogo->renderer, "assets/images/default.png");
        SDL_RenderCopy(jogo->renderer, backgroundTexture, NULL, NULL);
    }
    else if (jogo->status == GANHOU){
        backgroundTexture = IMG_LoadTexture(jogo->renderer, "assets/images/win.png");
        SDL_RenderCopy(jogo->renderer, backgroundTexture, NULL, NULL);
    }  
    else if (jogo->status == PERDEU){
        backgroundTexture = IMG_LoadTexture(jogo->renderer, "assets/images/game_over.png");
        SDL_RenderCopy(jogo->renderer, backgroundTexture, NULL, NULL);
    }

    int x_base = 150;
    int y_base = 370;
    int espacamento = 250; 
    int altura = 20;

    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        int x_torre = x_base + i * espacamento;
        int tamanho_pilha_temp = 0;
        int total = 0;

        Pilha pilha_temp;
        init(&pilha_temp);

        // Copie os discos da torre original para a pilha temporária
        while (!is_empty(jogo->torres[i])) {
            Tipo_Informacao disco;
            pop(jogo->torres[i], &disco);
            push(pilha_temp, disco);
            tamanho_pilha_temp++; // Atualize o tamanho da pilha temporária
        }

        // Imprime base
        int cores_base[4] = {255, 255, 255, 255};
        desenhar_retangulo(jogo->renderer, x_torre, y_base + 10, 100, 5, cores_base);

        for (int i = 0; i < 3; i++){

            int y_disco = y_base - i * altura;
            int largura = 5;
            int cores[4] = {255, 255, 255, 255};

            desenhar_retangulo(jogo->renderer, x_torre, y_disco -10, 5, altura, cores);
        }  

        while (tamanho_pilha_temp > 0) {
            Tipo_Informacao disco;
            pop(pilha_temp, &disco);
            tamanho_pilha_temp--; // Atualize o tamanho da pilha temporária

            int y_disco = y_base - total * altura;

            // Desenhe o disco (#) com uma borda
            if (disco == 1) {
                int cores[4] = {255, 0, 0, 255}; 
                desenhar_retangulo(jogo->renderer, x_torre, y_disco -10, 40, altura, cores);
            } else if (disco == 2) {
                int cores[4] = {0, 255, 0, 255}; 
                desenhar_retangulo(jogo->renderer, x_torre, y_disco -10, 60, altura, cores);

            } else if (disco == 3) {
                int cores[4] = {0, 0, 255, 255}; 
                desenhar_retangulo(jogo->renderer, x_torre, y_disco -10, 80, altura, cores);
            }

            // Empilhe de volta o disco na pilha original
            push(jogo->torres[i], disco);
            total++;
        }

        free_pilha(&pilha_temp);
    }

    if (jogo->status == PERDEU) {
        SDL_Delay(400);
    }
    SDL_DestroyTexture(backgroundTexture);
}

void desenhar_retangulo(SDL_Renderer *renderer, int x, int y, int largura, int altura, int cores[]){
    
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

void exibir_contador(Game jogo){

    SDL_Color textColor = {255, 255, 255}; // branco

    char texto[30];
    snprintf(texto, 30, "%d", jogo->contador);

    SDL_Surface *textSurface = TTF_RenderText_Solid(jogo->font, texto, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(jogo->renderer, textSurface);

    // Coordenadas para posicionar o texto na tela
    int textX = 10;
    int textY = 10;

    SDL_Rect textRect = {textX, textY, textSurface->w, textSurface->h};
    SDL_RenderCopy(jogo->renderer, textTexture, NULL, &textRect);

    // Libera as superfícies e texturas temporárias
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void exibir_botoes(Game jogo){
    for (int i = 0; i < 6; i++){
        SDL_SetRenderDrawColor(jogo->renderer, 255, 0, 0, 128); 
        SDL_SetRenderDrawBlendMode(jogo->renderer, SDL_BLENDMODE_BLEND); 
        SDL_RenderFillRect(jogo->renderer, &(jogo->buttons[i]));
    }
}