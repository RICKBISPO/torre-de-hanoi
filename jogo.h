#include "pilha.h"

typedef SDL_Rect Button;

void start_game(Pilha *pilha);

void start_buttons(Button buttons[]);

void end_game(SDL_Window *window, SDL_Renderer *renderer, Pilha torres[]);

void reset_game(Pilha torres[]);

void jogada(Pilha origem, Pilha destino);

bool verifica_acao(Pilha origem, Pilha destino);

void jogada_aleatoria(SDL_Renderer *renderer, Pilha pilha[], int pausa);

void to_print_torres(SDL_Renderer *renderer, Pilha torres[], int pausa);

void desenhar_torre(SDL_Renderer *renderer, int x, int y, int largura, int altura, int cores[]);

void pilha_to_vetor(Pilha pilha, int array[]);

// Imprime uma sombra vermelha que representa onde o botao está (apenas para depuracao)
void to_print_botoes(SDL_Renderer *renderer, Button botoes[]);