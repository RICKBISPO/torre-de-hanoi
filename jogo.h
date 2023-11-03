#include "pilha.h"

/**
 * Inicializa o jogo, ou seja, init() em 3 pilhas e
 * enche a ultima pilha com os valores (3,2,1)
 */
void start_game(Pilha *pilha);

/**
 * Funcao que faz uma jogada. Tira de uma torre
 * e coloca em outra
 */
void jogada(Pilha origem, Pilha destino);

/**
 * Funcao que verifica se é possivel fazer uma jogada:
 * Primeiro verifica se a pilha de origem não está vazia e
 * se a pilha de destino não está cheia
 * Depois compara os topos de cada pilha (topo-origem < topo-destino)
 * Ou se o destino está vazio
 */
bool verifica_acao(Pilha origem, Pilha destino);

/**
 * Se o jogador desiste, essa função executa vários testes de casos
 * E completa o jogo de onde o usuário terminou
 */
void jogada_aleatoria(SDL_Renderer *renderer, Pilha pilha[]);