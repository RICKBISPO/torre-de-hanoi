#include "pilha.h"
#include "jogo.h"

int main(int argc, char* argv[]) {
    
    srand((unsigned int)time(NULL));

    // Inicia tela
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar a SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Cria janela
    SDL_Window* window = SDL_CreateWindow("Torre de Hanoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    // Cria render da janela
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Cria um vetor de 3 Pihas 
    Pilha pilha[MAX_STACK_SIZE];
    start_game(pilha);

    SDL_Event evento;
    int rodando = 1;
    while (rodando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                rodando = 0;
            }
            to_print_todas_sdl(renderer, pilha);
            jogada_aleatoria(renderer, pilha);
            SDL_RenderPresent(renderer);
        }
    }
    
    // Fechar janela
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
