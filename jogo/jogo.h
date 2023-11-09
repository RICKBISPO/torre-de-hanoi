#include "pilha.h"
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif


/**
 * Constantes que definem o indice de cada disco
*/
#define PRIMEIRO_DISCO 0
#define SEGUNDO_DISCO 1
#define TERCEIRO_DISCO 2

/**
 * Constantes que definem o indice de cada torre
*/
#define TORRE_1 0
#define TORRE_2 1
#define TORRE_3 2

/**
 * Constantes que definem o indice de cada botao de opcao
*/
#define REINICIAR 3
#define DESISTIR 4
#define SAIR 5

/**
 * Numero de botoes
*/
#define NRO_BUTTONS 6

/**
 * typedef de SDL_Rect que vira Button
*/
typedef SDL_Rect Button;

/**
 * Inicializa as torres, enche a primeira torre com os discos
 * Inicializa também todos os 6 botoes, (3 referentes as torres e 3 de opcoes)
*/
void start_game(Pilha torres[], Button buttons[]);

/**
 * Limpa os ponteiros das torres e os ponteiros do SDL
*/
void end_game(Pilha torres[], SDL_Surface* icon, SDL_Renderer *renderer, SDL_Window *window);

/**
 * Limpa a torre e enche a primeira torre novamente
 * Também reseta as variaveis auxiliares e o contador
*/
void reset_game(Pilha torres[], int* temp,  int* primeiro, int* contador);

/**
 * Descobre se o click do mouse foi feito dentro de algum botao
*/
int descobrir_click(Button buttons[]);

/**
 * Faz a lógica de armazenar corretamente a variavel temp em origem ou destino
 * Após isso, chama a funcao fazer_jogada() e atualiza o contador de jogadas
*/
void jogada(Pilha torres[], int temp,  int* primeiro, int* contador, int* origem, int* destino);

/**
 * Faz a jogada, pop[origem] - push[destino]
*/
bool fazer_jogada(Pilha origem, Pilha destino);

/**
 * Funcao que realiza o jogo automaticamente quando o usuario desistir
*/
void jogada_aleatoria(SDL_Renderer *renderer, Pilha pilha[], int pausa);

/**
 * Funcao responsável por diminuir o numero de jogadas quando o usuario desistir
*/
void diminuir_jogadas(int torre1[], int torre2[], int torre3[], int* origem, int* destino);

/**
 * Se a torre 1 ou 2 estiver cheia, executa essa funcao que é um gabarito de 7 passos
 * para finalizar o jogo conforme qual torre está cheia
*/
void gabarito_torre(SDL_Renderer *renderer, Pilha torres[], int pausa);

/**
 * Exibe todas as torres
*/
void to_print_torres(SDL_Renderer *renderer, Pilha torres[], int pausa);

/**
 * Desenha um retangulo conforme os parametros de construcao do retangulo
*/
void desenhar_torre(SDL_Renderer *renderer, int x, int y, int largura, int altura, int cores[]);

/**
 * Copia a pilha para um vetor, sem quebrar o TAD
*/
void pilha_to_vetor(Pilha pilha, int array[]);

/**
 * Imprime uma sombra vermelha que representa onde o botao está (apenas para depuracao)
*/
void to_print_botoes(SDL_Renderer *renderer, Button botoes[]);