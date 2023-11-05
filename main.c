#include "pilha.h"
#include "jogo.h"

typedef struct Button{
    SDL_Rect rect;
    int index;
} Button;

#define WIDTH 800
#define HEIGHT 500

void to_print_botoes(SDL_Renderer *renderer, Button botoes[]);

int main(int argc, char *argv[]){

    // Inicia aleatorio
    srand((unsigned int)time(NULL));

    // Inicia tela
    SDL_Init(SDL_INIT_VIDEO);

    // Cria janela
    SDL_Window *window = SDL_CreateWindow("Torre de Hanoi", 
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        WIDTH, 
                                        HEIGHT, 
                                        SDL_WINDOW_SHOWN);

    // Cria render da janela
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Cria um vetor de 3 Pilhas
    Pilha pilha[MAX_STACK_SIZE];
    start_game(pilha);

    // Cria 3 botoes para as pilhas
    Button buttons[3];

    // cria os 3 botoes(formato)
    for (int i = 0; i < 3; i++){
        buttons[i].rect = (SDL_Rect)
                                    {
                                     100 + i * 250, // x: horizontal em relacao a borda
                                     350,           // y: vertical em relacao ao comeco do programa
                                     100,           // w: largura do retangulo 
                                     65             // h: altura do retangulo 
                                     };
        buttons[i].index = i;
    }

    SDL_Event evento;
    int parou = false;

    // Variavel que serve para o pop e push
    int origem;
    int destino;
    int temp;
    int primeiro = true;
    int contador = 0;

    while (!parou && !is_full(pilha[2])){
        
        while (SDL_PollEvent(&evento) != 0){


            if (evento.type == SDL_QUIT){
                parou = true;
            }
            else if (evento.type == SDL_MOUSEBUTTONDOWN){

                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                for (int i = 0; i < 3; i++) {
                    if (mouseX >= buttons[i].rect.x && mouseX <= (buttons[i].rect.x + buttons[i].rect.w) &&
                        mouseY >= buttons[i].rect.y && mouseY <= (buttons[i].rect.y + buttons[i].rect.h)) {
                        printf("indice %d\n", buttons[i].index);

                        temp = buttons[i].index;
                    }
                }

                if (primeiro){
                    origem = temp;
                    primeiro = false;
                }
                else if(!primeiro){
                    destino = temp;
                    primeiro = true;

                    if (destino != origem){
                        if (verifica_acao(pilha[origem], pilha[destino])){
                            jogada(pilha[origem], pilha[destino]);
                            contador++; 
                        }
                    }
                    
                    system("cls");
                    printf("jogadas: %d\n", contador);
                }
        
            }   
        }

        // jogada_aleatoria(renderer, pilha);
    
    
        // exibe as torres
        to_print_todas_sdl(renderer, pilha);
    
        // exibe os botoes
        to_print_botoes(renderer, buttons);

        // atualiza a tela
        SDL_RenderPresent(renderer);
    }

    // Fechar janela
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Limpar pilha
    for (int i = 0; i < 3; i++){
        freePilha(&pilha[i]);
    }

    return 0;
}

void to_print_botoes(SDL_Renderer *renderer, Button botoes[]){
    for (int i = 0; i < 3; i++){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // botao transparente
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderer, &botoes[i].rect);
    }
}