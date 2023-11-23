#include "pilha.h"
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

/* Usa cls se windows e clear se linux*/
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

#define JOGANDO 0
#define PERDEU -1
#define GANHOU 1

/* Constantes que definem o indice de cada disco */
#define PRIMEIRO_DISCO 0
#define SEGUNDO_DISCO 1
#define TERCEIRO_DISCO 2

/* Constantes que definem o indice de cada torre */
#define TORRE_1 0
#define TORRE_2 1
#define TORRE_3 2

/* Constantes que definem o indice de cada botao de opcao */
#define REINICIAR 3
#define DESISTIR 4
#define SAIR 5

/* Numero de botoes */
#define NRO_BUTTONS 6

/* Largura */
#define WIDTH 800

/* Altura */
#define HEIGHT 500

/**
 * typedef de SDL_Rect que vira Button
*/
typedef SDL_Rect Button;

struct jogo{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *icon;
    TTF_Font *font;
    Pilha torres[3];
    Button buttons[NRO_BUTTONS];
    SDL_Event evento;
    int contador;
    int status;
    int primeiro;
    int origem;
    int destino;
};

typedef struct jogo* Game;

Game iniciar_jogo();

void iniciar_torres(Pilha torres[]);

void iniciar_botoes(Button buttons[]);

void end_game(Game jogo);

void reset_game(Game jogo);

int descobrir_click(Game jogo);

void jogada(Game jogo, int temp);

bool fazer_jogada(Pilha origem, Pilha destino);

void resolver_jogo(Game jogo);

void gabarito_torre(Game jogo);

void pilha_to_vetor(Pilha pilha, int array[]);

void diminuir_jogada(Game jogo);

void exibir_torres(Game jogo);

void desenhar_retangulo(SDL_Renderer *renderer, int x, int y, int largura, int altura, int cores[]);

void exibir_contador(Game jogo);

void exibir_botoes(Game jogo);