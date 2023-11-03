void menu();

int main(void){

    srand((unsigned int)time(NULL));

    Pilha pilha[MAX_STACK_SIZE];
    int origem, destino, desiste = false;

    start_game(pilha);

    do{
        to_print_todas(pilha);

        menu();
        scanf("%d%d", &origem, &destino);

        if (origem == 0 || destino == 0){
            desiste = true;
        }
        else{
            origem--;
            destino--;

            if (verifica_acao(pilha[origem], pilha[destino])){
                jogada(pilha[origem], pilha[destino]);
            }
        }

    } while (!is_full(pilha[2]) && !desiste);

    if (!desiste){
        printf("----Voce ganhou!----\n");
    }
    else{
        jogada_aleatoria(pilha);
        printf("----Voce Perdeu e o PC fez por voce!----\n");
    }

    return 0;
}

void menu(){
    printf("Escolha uma torre de origem e uma de destino:\n");
    printf("(1) torre 1 || (2) torre 2 || (3) torre 3\n");
    printf("Ou digite '0 0' para desistir\n");  
}