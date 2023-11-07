#include "pilha.h"
#include "jogo.h"

#define WIDTH 800
#define HEIGHT 500

#define REINICIAR 3
#define DESISTIR 4
#define SAIR 5

int main(int argc, char *argv[]){

    // Inicia aleatorio
    srand((unsigned int)time(NULL));

    SDL_Surface* icon = SDL_LoadBMP("assets/icone.bmp");

    // Inicia SDL e cria janela
    // Cria janela: SDL_CreateWindow(titulo do app, posicao X em relacao ao monitor, posicao Y em relacao ao monitor, largura, altura, comportamento da janela)
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Torre de Hanoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_SetWindowIcon(window, icon);

    // Cria render da janela
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Cria torres e botoes
    Pilha torres[3];
    start_game(torres);

    Button buttons[6];
    start_buttons(buttons);

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
                        else if (i == REINICIAR){
                            reset_game(torres);
                            contador = 0;
                            primeiro = true;
                            temp = 3;
                            SDL_RenderPresent(renderer);
                            continue;
                        }
                        else if(i == DESISTIR){
                            jogada_aleatoria(renderer, torres, true);
                            continue;
                        }
                        else if(i == SAIR){
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

                        if (verifica_acao(torres[origem], torres[destino])){
                            jogada(torres[origem], torres[destino]);
                            contador++; 
                        }
                        system("cls");
                        printf("\njogadas: %d\n", contador);
                    }
                }
                
            }   
        }

        // exibe as torres e plano de fundo
        to_print_torres(renderer, torres, false);
    
        // to_print_botoes(renderer, buttons);

        // atualiza a tela
        SDL_RenderPresent(renderer);
    }

    end_game(window, renderer, icon, torres);

    return 0;
}

