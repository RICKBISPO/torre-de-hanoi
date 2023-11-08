#include "pilha.h"
#include "jogo.h"

#define WIDTH 800
#define HEIGHT 500

int main(int argc, char *argv[]){

    srand((unsigned int)time(NULL));

    // Inicializa SDL, window e renderer
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Torre de Hanoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Inicializa o icone do aplicativo
    SDL_Surface *icon = SDL_LoadBMP("assets/icone.bmp");
    SDL_SetWindowIcon(window, icon);

    Pilha torres[3];
    Button buttons[NRO_BUTTONS];

    start_game(torres, buttons);

    SDL_Event evento;
    int parou = false;

    int origem, destino, contador = 0, primeiro = true;

    while (!parou){
        while (SDL_PollEvent(&evento) != 0){

            if (evento.type == SDL_QUIT){
                parou = true;
            }
            else if (evento.type == SDL_MOUSEBUTTONDOWN){

                // Acha o indice do botao que foi clicado
                int temp = descobrir_click(buttons);

                // Faz uma jogada se o indice for entre 0 e 2
                if (temp >= 0 && temp < 3) jogada(torres, temp, &primeiro, &contador, &origem, &destino);
                
                // Reincia
                else if (temp == REINICIAR) reset_game(torres, &temp, &primeiro, &contador);
                
                // Desiste
                else if (temp == DESISTIR) jogada_aleatoria(renderer, torres, true);
                
                // Sai do jogo
                else if (temp == SAIR) parou = true;
            
            }
        }
        to_print_torres(renderer, torres, false);
        // to_print_botoes(renderer, buttons);
        SDL_RenderPresent(renderer);
    }

    end_game(torres, icon, renderer, window);

    return 0;
}