#include "pilha.h"
#include "jogo.h"

typedef SDL_Rect Button;

#define WIDTH 800
#define HEIGHT 500

// Imprime uma sombra vermelha que representa onde o botao está
void to_print_botoes(SDL_Renderer *renderer, Button botoes[]);

// free nas torres e inicia novamente
void resetar_jogo(Pilha pilha[]);

int main(int argc, char *argv[]){

    // Inicia aleatorio
    srand((unsigned int)time(NULL));

    // Inicia SDL e cria janela
    // Cria janela: SDL_CreateWindow(titulo do app, posicao X em relacao ao monitor, posicao Y em relacao ao monitor, largura, altura, comportamento da janela)
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Torre de Hanoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    // Cria render da janela
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Cria um vetor de 3 Pilhas
    Pilha pilha[3];
    start_game(pilha);

    // 3 botoes para torres e 3 para torres
    Button buttons[6];

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

    // Variaveis de evento e condição de parada
    SDL_Event evento;
    int parou = false;

    // Variaveis de pop push, temp e contador de jogadas e indicador de origem/destino
    int origem, destino, temp, contador = 0, primeiro = true;

    // Enquanto não fechar a janela && a terceira torre nao estiver cheia
    while (!parou){
        
        // Esse while depende de eventos, nesse caso são:
        // Se fechar a janela e se ocorrer o clique do mouse
        while (SDL_PollEvent(&evento) != 0){

            // Se o evento for a janela fechando, encerra o programa
            if (evento.type == SDL_QUIT){
                parou = true;
            }
            // Se o evento for o click do mouse
            else if (evento.type == SDL_MOUSEBUTTONDOWN){

                // Guarda as coordenadas de onde o mouse clicou
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Verifica se o mouse clicou dentro de alguma torre ou em alguma opcao
                for (int i = 0; i < 6; i++) {
                    if (mouseX >= buttons[i].x && mouseX <= (buttons[i].x + buttons[i].w) &&
                        mouseY >= buttons[i].y && mouseY <= (buttons[i].y + buttons[i].h)) {

                        if (i < 3){
                            printf("indice %d\n", i);
                            temp = i;
                        }
                        else if (i == 3){ // reiniciar jogo
                            resetar_jogo(pilha);
                            contador = 0;
                            primeiro = true;
                            temp = 3;
                            SDL_RenderPresent(renderer);
                            continue;
                        }
                        else if(i == 4){ // desistir
                            jogada_aleatoria(renderer, pilha, true);
                            continue;
                        }
                        else if(i == 5){ // Sair
                            parou = true;
                            break;
                        }
                    }
                }

                if (temp == 0 || temp == 1 || temp == 2){
                    if (primeiro){
                        origem = temp;
                        primeiro = false;
                    }
                    else if(!primeiro){
                        destino = temp;
                        primeiro = true;

                        if (verifica_acao(pilha[origem], pilha[destino])){
                            jogada(pilha[origem], pilha[destino]);
                            contador++; 
                        }
                        system("cls");
                        printf("\njogadas: %d\n", contador);
                    }
                }
                
            }   
        }

        // exibe as torres e plano de fundo
        to_print_todas_sdl(renderer, pilha, false);
    
        // to_print_botoes(renderer, buttons);

        // atualiza a tela
        SDL_RenderPresent(renderer);
    }

    // Limpar pilha
    for (int i = 0; i < 3; i++){
        freePilha(&pilha[i]);
    }

    // Fechar janela e limpar ponteiros
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void resetar_jogo(Pilha pilha[]){
    for (int i = 0; i < 3; i++){
        freePilha(&pilha[i]);
    }

    start_game(pilha);
}

void to_print_botoes(SDL_Renderer *renderer, Button botoes[]){
    for (int i = 0; i < 6; i++){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); 
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
        SDL_RenderFillRect(renderer, &botoes[i]);
    }
}