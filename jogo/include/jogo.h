#include "pilha.h"
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

/**
 * Struct que representa todas as funcionalidades do jogo
*/
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

/**
 * Ponteiro para a struct jogo
*/
typedef struct jogo* Game;

/**
 * Funcao que aloca espaco para uma struct jogo,
 * inicializa a janela, renderizador, o icone, a fonte,
 * as torres, os botoes e as variaveis de jogo
*/
Game iniciar_jogo();

/**
 * Inicializa 3 torres e enche a primeira torre com os discos = {3, 2, 1}
*/
void iniciar_torres(Pilha torres[]);

/**
 * Cria 6 botoes, 3 referentes as torres e 3 referentes aos botoes de
 * reiniciar, desistir e sair.
*/
void iniciar_botoes(Button buttons[]);

/**
 * Limpa todas as alocações de memória que foram usadas
*/
void end_game(Game jogo);

/**
 * Limpa as alocações de memoria das torres e inicializa novas,
 * além de resetar as variaveis de jogo
*/
void reset_game(Game jogo);

/**
 * Descobre se o mouse clicou em algum dos botoes
*/
int descobrir_click(Game jogo);

/**
 * Funcao que faz a logica de primeira ou segunda jogada, 
 * considera se é a primeira jogada do jogador ou nao.
*/
void jogada(Game jogo, int temp);

/**
 * Funcao que verifica as regras do jogo, e se estiver certo, faz a jogada
*/
bool fazer_jogada(Pilha origem, Pilha destino);

/**
 * Funcao que resolve o jogo através de uma sequencia de passos,
 * essa função é chamada apenas quando o usuario desiste do jogo
*/
void resolver_jogo(Game jogo);

/**
 * Funcao usada por resolver_jogo() que executa o gabarito da torre
 * caso a primeira ou a segunda torres estejam ordenadas
*/
void gabarito_torre(Game jogo);

/**
 * Funcao que copia as informacoes da torre para um array, 
 * usando pop e push
*/
void pilha_to_vetor(Pilha pilha, int array[]);

/**
 * Funcao usada por resolver_jogo() que faz algumas verificacoes 
 * que diminuem o numero de jogadas necessarias
*/
void diminuir_jogada(Game jogo);

/**
 * Funcao que exibe as 3 torres com o SDL2
*/
void exibir_torres(Game jogo);

/**
 * Funcao que desenha os triangulos das torres
*/
void desenhar_retangulo(SDL_Renderer *renderer, int x, int y, int largura, int altura, int cores[]);

/**
 * Exibe o contador na tela
*/
void exibir_contador(Game jogo);

/**
 * Exibe uma sombra dos botoes na tela (Apenas para depuração)
*/
void exibir_botoes(Game jogo);