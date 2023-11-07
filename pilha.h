#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

void freePilha(Pilha* pilha);