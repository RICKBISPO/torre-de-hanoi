#include "pilha.h"
#include "jogo.h"

// Botao que representa as 3 torres
typedef struct Button{
    SDL_Rect rect;
    int index;
} Button;

// Largura e altura
#define WIDTH 800
#define HEIGHT 500

// Imprime os 3 botoes que representam as torres
void to_print_botoes(SDL_Renderer *renderer, Button botoes[]);

int main(int argc, char *argv[]){

    // Inicia aleatorio
    srand((unsigned int)time(NULL));

    // Inicia tela
    SDL_Init(SDL_INIT_VIDEO);

    // Cria janela
    SDL_Window *window = SDL_CreateWindow("Torre de Hanoi", // Titulo do aplcativo
                                        SDL_WINDOWPOS_CENTERED, // Deixa o aplicativo centralizado
                                        SDL_WINDOWPOS_CENTERED, // Deixa o aplicativo centralizado
                                        WIDTH, // Largura
                                        HEIGHT, // Altura
                                        SDL_WINDOW_SHOWN // Como a janela vai ser exibida
                                        );

    // Cria render da janela
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Cria um vetor de 3 Pilhas
    Pilha pilha[3];
    start_game(pilha);

    // Cria 3 botoes para as pilhas
    // E cria o tamanho de cada um
    Button buttons[3];

    for (int i = 0; i < 3; i++){
        buttons[i].rect = (SDL_Rect)
                                    {
                                     100 + i * 250, // x: horizontal em relacao a borda
                                     320,           // y: vertical em relacao ao comeco do programa
                                     100,           // w: largura do retangulo 
                                     65             // h: altura do retangulo 
                                     };
        buttons[i].index = i;
    }

    // Variaveis de evento e condição de parada
    SDL_Event evento;
    int parou = false;

    // Variavel que serve para o pop e push
    int origem;
    int destino;
    int temp;

    // Variavel que indica se a torre escolhida é a primeira ou nao
    int primeiro = true;

    // Contador de jogadas
    int contador = 0;

    // Enquanto não fechar a janela && a terceira torre nao estiver cheia
    while (!parou && !is_full(pilha[2])){
        
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

                // Verifica se o mouse clicou dentro de alguma torre
                for (int i = 0; i < 3; i++) {
                    if (mouseX >= buttons[i].rect.x && mouseX <= (buttons[i].rect.x + buttons[i].rect.w) &&
                        mouseY >= buttons[i].rect.y && mouseY <= (buttons[i].rect.y + buttons[i].rect.h)) {

                        printf("indice %d\n", buttons[i].index);
                        temp = buttons[i].index;
                    }
                }
                // Se for o primeiro click ou nao

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
                    printf("jogadas: %d\n", contador);
                }
            }   
        }

        // jogada_aleatoria(renderer, pilha);
    
        // exibe as torres e plano de fundo
        to_print_todas_sdl(renderer, pilha);
    
        // exibe os botoes
        to_print_botoes(renderer, buttons);

        // atualiza a tela
        SDL_RenderPresent(renderer);
    }

    // Fechar janela e limpar ponteiros
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
    for (int i = 0; i < 3; i++)
    {
        // Desenha um botao transparente que fica encima da torre
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 
        SDL_RenderFillRect(renderer, &botoes[i].rect);
    }
}