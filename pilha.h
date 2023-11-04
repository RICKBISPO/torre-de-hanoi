#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_STACK_SIZE 3

typedef struct stack* Pilha;

typedef int Tipo_Informacao;

void init(Pilha* pilha);

bool is_full(Pilha pilha);

bool is_empty(Pilha pilha);

bool push(Pilha pilha, Tipo_Informacao elemento);

bool pop(Pilha pilha, Tipo_Informacao* elemento);

/**
 * Limpa o espaço de memoria onde foi alocado uma pilha
*/
void freePilha(Pilha* pilha);

/**
 * Guarda as informações da pilha dentro de um vetor
*/
void pilha_to_vetor(Pilha pilha, int* array, int size);

/**
 * Imprime todas as torres usando SDL
*/
void to_print_todas_sdl(SDL_Renderer *renderer, Pilha torres[]);
